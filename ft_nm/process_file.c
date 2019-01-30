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

#include "ft_nm.h"

int			invalid_file(char *filename)
{
	struct stat st;
	int			fd;

	if (-1 == (fd = (open(filename, O_RDONLY))))
		return (-1);
	if (-1 == fstat(fd, &st))
		return (-1);
	if (st.st_mode & S_IFDIR)
	{
		ft_printf("ft_nm: %s: Is a directory.\n", filename);
		return (-1);
	}
	return (0);
}

int			invalid_file_type(char *filename)
{
	ft_printf("ft_nm: %s The file was not recognized as a valid object file\n",
				filename);
	return (-1);
}

int			process_file(char *filename, int options)
{
	t_bin				*bin_struct;
	uint8_t				*bin;
	uint32_t			header;
	int					rv;
	t_env				*env;

	if (-1 == invalid_file(filename))
		return (-1);
	if (NULL == (bin_struct = get_bin(filename)))
		return (-1);
	bin = bin_struct->head;
	if (!(env = (t_env*)ft_memalloc(sizeof(t_env))))
		return (-1);
	env = get_env(env, bin);
	header = *(uint32_t*)bin;
	if (is_archive(bin))
		rv = process_archive(env, filename, options);
	else if (header == FAT_MAGIC_64 || header == FAT_CIGAM)
		rv = process_fat(env, options);
	else if (header == MH_MAGIC_64 || header == MH_MAGIC)
		rv = process_macho(env, options);
	else
		rv = invalid_file_type(filename);
	free_bin(bin_struct);
	free(env);
	return (rv);
}
