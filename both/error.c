/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:04:31 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 18:09:06 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static void		print_msg(int error, char *file, int line)
{
	char *msg;

	msg = "ERROR";
	msg = (error == CORRUPT_FILE) ? "Corrupt file" : msg;
	msg = (error == INVALID_FILE) ? "Invalid file" : msg;
	msg = (error == FSTAT_FAILED) ? "fstat failed" : msg;
	msg = (error == OPEN_FAILED) ? "open failed" : msg;
	msg = (error == CLOSE_FAILED) ? "close failed" : msg;
	msg = (error == MMAP_FAILED) ? "mmap failed" : msg;
	msg = (error == NO_SYMTAB) ? "no symtab" : msg;
	msg = (error == INVALID_ARG) ? "Invalid arg" : msg;
	msg = (error == MALLOC_FAILED) ? "malloc failed" : msg;
	(void)file;
	(void)line;
}

void			*ft_error(int error, char *file, int line)
{
	print_msg(error, file, line);
	return (NULL);
}

int				ft_error_one(int error, char *file, int line)
{
	print_msg(error, file, line);
	return (-1);
}
