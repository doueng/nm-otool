/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:25:18 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 18:07:38 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int			main(int argc, char *argv[])
{
	int rv;

	if (argc < 2)
		return (ft_error_one(INVALID_ARG, __FILE__, __LINE__));
	rv = 0;
	while (*++argv)
	{
		rv = process_file(*argv, 0);
	}
	return (rv);
}
