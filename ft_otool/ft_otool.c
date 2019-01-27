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

static int	get_options(char *op_str)
{
	int options;

	options = 0;
	options |= ft_strchr(op_str, 't') ? DUMP_OP : 0;
	return (options);
}

int			main(int argc, char *argv[])
{
	int options;

	if (argc < 3)
		return (-1);
	if (!(options = get_options(*++argv)))
		return (-1);
	while (*++argv)
	{
		if (options | DUMP_OP && -1 == process_file(*argv, options))
			return (-1);
	}
	return (0);
}
