/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:07:48 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 18:10:00 by dengstra         ###   ########.fr       */
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
	if (st.st_size < 10)
		return (ft_error_one(CORRUPT_FILE, __FILE__, __LINE__));
	if (st.st_mode & S_IFDIR)
		return (ft_error_one(INVALID_FILE, __FILE__, __LINE__));
	if (-1 == close(fd))
		return (ft_error_one(CLOSE_FAILED, __FILE__, __LINE__));
	return (0);
}

static int	processor(t_env *env)
{
	uint32_t			header;

	header = *((uint32_t*)(env->filehead));
	if (header == FAT_MAGIC_64 || header == FAT_CIGAM)
		return (process_fat(env));
	else if (header == MH_MAGIC_64
			|| header == MH_MAGIC
			|| header == MH_CIGAM
			|| header == MH_CIGAM_64)
		return (process_macho(env));
	return (ft_error_one(INVALID_FILE, __FILE__, __LINE__));
}

int			process_file(char *filename, int options)
{
	int					rv;
	t_env				*env;

	rv = 0;
	if (-1 == invalid_file(filename))
		return (-1);
	if (!(env = get_env(filename, options)))
		return (-1);
	if (-1 == processor(env))
		rv = ft_error_one(INVALID_FILE, __FILE__, __LINE__);
	free(env);
	return (rv);
}
