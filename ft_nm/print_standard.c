/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_standard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:13:02 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 16:49:46 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char			get_type_letter(t_nmtree *symbol)
{
	char			letter;
	uint8_t			type;
	uint8_t			nsect;
	struct nlist_64	*nlist;

	nlist = symbol->nlist;
	type = nlist->n_type & N_TYPE;
	nsect = nlist->n_sect;
	letter = 'S';
	letter = type == N_UNDF ? 'U' : letter;
	letter = type == N_ABS ? 'A' : letter;
	letter = type == N_INDR ? 'I' : letter;
	letter = nsect > 0 ? 'T' : letter; // fix
	return (nlist->n_type & N_EXT ? letter : letter | 0x20);
}

void				print_standard(t_nmtree *symbol)
{
	struct nlist_64	*nlist;

	nlist = symbol->nlist;
	if (nlist->n_value == 0 && nlist->n_type == N_EXT)
		ft_printf("%16c U %s\n", ' ', symbol->name);
	else
		ft_printf("%016llx %c %s\n", nlist->n_value, get_type_letter(symbol),
					symbol->name);
}
