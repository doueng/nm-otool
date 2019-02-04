/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:25:18 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 13:25:19 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

/* static int	get_options(char *op_str) */
/* { */
/* 	int options; */

/* 	options = 0; */
/* 	/\* options |= ft_strchr(op_str, 't') ? DUMP_OP : 0; *\/ */
/* 	return (options); */
/* } */

int			main(int argc, char *argv[])
{
	int rv;

	if (argc < 2)
		return (ft_error_one(INVALID_ARG, __FILE__, __LINE__));
	/* if (!(options = get_options(*++argv))) */
		/* return (-1); */
	rv = 0;
	while (*++argv)
	{
		rv = process_file(*argv, 0);
	}
	return (rv);
}
