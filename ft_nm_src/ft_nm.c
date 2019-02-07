/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:05:10 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 18:57:41 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	get_options(char *op_str)
{
	int options;

	options = 0;
	options |= NM_OP;
	if (op_str[0] != '-')
		return (options);
	if (ft_strequ(op_str, "-"))
		return (ft_error_one(INVALID_OPTION, __FILE__, __LINE__));
	while (*++op_str)
	{
		options |= (*op_str == 'r') ? REV_OP : 0;
		options |= (*op_str == 'v') ? VAL_OP : 0;
		options |= (*op_str == 's') ? SYM_OP : 0;
		options |= (*op_str == 'u') ? UNDEF_OP : 0;
		options |= (*op_str == 't') ? TEXT_OP : 0;
		if (ft_strchr("rvsut", *op_str) == NULL)
			return (ft_error_one(INVALID_OPTION, __FILE__, __LINE__));
	}
	return (options);
}

int			main(int argc, char *argv[])
{
	int options;
	int rv;

	options = 1;
	if (argc == 1)
		return (process_file("a.out", 0));
	if (-1 == (options = get_options(*++argv)))
		return (-1);
	if (options > 1)
		argv++;
	if (!*argv)
		return (ft_error_one(INVALID_OPTION, __FILE__, __LINE__));
	while (*argv)
	{
		if ((argc - (options > 1 ? 1 : 0)) > 2)
			ft_printf("\n%s:\n", *argv);
		rv = process_file(*argv, options);
		argv++;
	}
	return (rv);
}
