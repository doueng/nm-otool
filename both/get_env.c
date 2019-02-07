/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 18:05:55 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 18:10:58 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static t_env		*get_fileinfo(t_env *env, char *filename)
{
	int			fd;
	struct stat	st;

	if (-1 == (fd = open(filename, O_RDONLY)))
		return (ft_error(OPEN_FAILED, __FILE__, __LINE__));
	if (-1 == fstat(fd, &st))
		return (ft_error(FSTAT_FAILED, __FILE__, __LINE__));
	env->filename = filename;
	env->filesize = st.st_size;
	env->filehead = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (-1 == close(fd))
		return (ft_error(CLOSE_FAILED, __FILE__, __LINE__));
	if (MAP_FAILED == env->filehead)
		return (ft_error(MMAP_FAILED, __FILE__, __LINE__));
	return (env);
}

static char			is_64(uint32_t magic)
{
	return (magic == MH_MAGIC_64
		|| magic == MH_CIGAM_64
		|| magic == FAT_CIGAM_64
		|| magic == FAT_MAGIC_64);
}

static char			is_rev_bytes(uint32_t magic)
{
	return (magic == MH_CIGAM
		|| magic == MH_CIGAM_64
		|| magic == FAT_CIGAM
		|| magic == FAT_CIGAM_64);
}

t_env				*update_env(t_env *env)
{
	uint32_t magic;

	magic = env->macho->magic;
	env->is_64 = is_64(magic);
	env->rev_bytes = is_rev_bytes(magic);
	env->ldcmds = incbytes(env,
						env->macho,
						env->is_64
							? sizeof(struct mach_header_64)
							: sizeof(struct mach_header));
	if (!env->ldcmds)
		return (ft_error(CORRUPT_FILE, __FILE__, __LINE__));
	if (env->is_64 == 0
		&& env->rev_bytes == 0
		&& ft_memcmp(env->macho, ARMAG, SARMAG) != 0
		&& magic != MH_MAGIC
		&& magic != FAT_MAGIC)
		return (ft_error(INVALID_FILE, __FILE__, __LINE__));
	return (env);
}

t_env				*get_env(t_env *env, char *filename, int options)
{
	if (!(get_fileinfo(env, filename)))
		return (NULL);
	env->macho = env->filehead;
	env->is_nm = options & NM_OP;
	env->options = options ^ NM_OP;
	if (!update_env(env))
		return (NULL);
	return (env);
}
