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
	options |= ft_strchr(op_str, 'r') ? REV_OP : 0;
	options |= ft_strchr(op_str, 'v') ? VAL_OP : 0;
	options |= ft_strchr(op_str, 's') ? SYM_OP : 0;
	return (options);
}

int			main(int argc, char *argv[])
{
	int options;
	int rv;

	if (argc > 1 && 1 < (options = get_options(*++argv)))
		argv++;
	if (argc < 2)
		process_file("a.out", options);
	while (*argv)
	{
		if ((argc - (options > 1 ? 1 : 0)) > 2)
			ft_printf("\n%s:\n", *argv);
		rv = process_file(*argv, options);
		argv++;
	}
	return (rv);
}
