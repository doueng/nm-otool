/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:04:31 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 16:07:30 by dengstra         ###   ########.fr       */
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
	ft_putstr_fd("ERROR:\t", 2);
	/* (void)file; */
	/* (void)line; */
	ft_putendl_fd(msg, 2);
	ft_putstr_fd("FILE:\t", 2);
	ft_putendl_fd(file, 2);
	ft_putstr_fd("LINE:\t", 2);
	ft_putendl_fd(ft_itoa(line), 2);
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
