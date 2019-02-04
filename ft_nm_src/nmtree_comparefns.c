/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmtree_comparefns.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:07:29 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 16:07:30 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		alpha_order_compare(t_nmtree *new, t_nmtree *to_compare, int options)
{
	int strcmp;
	int rev;

	rev = options & REV_OP ? -1 : 1;
	if (0 != (strcmp = ft_strcmp(to_compare->name, new->name))) // change back to strcmp
		return (rev * strcmp);
	return (rev * (to_compare->nlist->n_value - new->nlist->n_value));
}

int		num_order_compare(t_nmtree *new, t_nmtree *to_compare, int options)
{
	int rev;

	rev = options & REV_OP ? -1 : 1;
	return (rev * (to_compare->nlist->n_value - new->nlist->n_value));
}

int		symbol_order_compare(t_nmtree *new, t_nmtree *to_compare, int options)
{
	(void)options;
	(void)new;
	(void)to_compare;
	return (1);
}