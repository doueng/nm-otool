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

void	*ft_error(char *error_text)
{
	ft_printf("%s\n", error_text);
	return (NULL);
}

int		ft_error_one(char *error_text)
{
	ft_printf("%s\n", error_text);
	return (-1);
}
