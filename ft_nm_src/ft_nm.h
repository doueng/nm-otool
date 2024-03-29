/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:05:15 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 18:59:19 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_NM_H
# define __FT_NM_H

# include "../both/nm_otool.h"

typedef struct				s_nmtree
{
	char					*name;
	t_env					*env;
	struct nlist_64			*nlist;
	struct s_nmtree			*left;
	struct s_nmtree			*right;
}							t_nmtree;

typedef struct				s_btinfo
{
	uint32_t				nsyms;
	struct nlist_64			*nlist;
	char					*symtabstr;
}							t_btinfo;

t_btinfo					*get_btinfo(t_env *env,
										struct symtab_command *symtab);
t_nmtree					*insert_symbols(t_env *env,
										t_btinfo *btinfo);
void						print_tree(t_nmtree *symbol,
										void (*print_function)(t_nmtree *));
void						print_standard(t_nmtree *symbol);
int							alpha_order_compare(t_nmtree *new,
										t_nmtree *to_compare);
int							value_order_compare(t_nmtree *new,
										t_nmtree *to_compare);
int							symbol_order_compare(t_nmtree *new,
										t_nmtree *to_compare);
#endif
