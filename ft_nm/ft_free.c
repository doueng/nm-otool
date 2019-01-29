/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:05:04 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 16:05:06 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	free_btinfo(t_btinfo *btinfo)
{
	free(btinfo->nlist);
	free(btinfo->symtabstr);
	free(btinfo);
}

void	free_nmtree(t_nmtree *symbol)
{
	if (!symbol)
		return ;
	if (symbol->left)
		free_nmtree(symbol->left);
	if (symbol->right)
		free_nmtree(symbol->right);
	free(symbol);
}
