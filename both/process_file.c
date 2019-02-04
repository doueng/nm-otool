/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:07:48 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 16:16:01 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static int	invalid_file(char *filename)
{
	struct stat st;
	int			fd;

	if (-1 == (fd = (open(filename, O_RDONLY))))
		return (ft_error_one(OPEN_FAILED, __FILE__, __LINE__));
	if (-1 == fstat(fd, &st))
		return (ft_error_one(FSTAT_FAILED, __FILE__, __LINE__));
	if (st.st_size < 100) // check
		return (ft_error_one(CORRUPT_FILE, __FILE__, __LINE__));
	if (st.st_mode & S_IFDIR)
		return (ft_error_one(INVALID_FILE, __FILE__, __LINE__));
	return (close(fd));
}

static int	processor(t_env *env, char *filename, int options)
{
	uint32_t			header;

	header = *((uint32_t*)(env->filehead));
	if (ft_memcmp(env->filehead, ARMAG, SARMAG) == 0)
		return (process_archive(env, filename, options));
	else if (header == FAT_MAGIC_64 || header == FAT_CIGAM)
		return (process_fat(env, options));
	else if (header == MH_MAGIC_64 || header == MH_MAGIC)
		return (process_macho(env, options));
	return (ft_error_one(INVALID_FILE, __FILE__, __LINE__));
}

int			process_file(char *filename, int options)
{
	int					rv;
	t_env				*env;

	rv = 0;
	if (-1 == invalid_file(filename))
		return (-1);
	if (!(env = get_env(filename)))
		return (-1);
	if (-1 == processor(env, filename, options))
		rv = -1;
	free(env);
	return (rv);
}
