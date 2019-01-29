/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:04:35 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/28 18:07:50 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int		free_bin(t_bin *bin)
{
	if (-1 == munmap(bin->head, bin->size))
		return (-1);
	free(bin);
	return (0);
}

void	free_env(t_env *env)
{
	free(env);
}
