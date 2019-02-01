/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmtree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:07:42 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 16:16:30 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_nmtree		*create_nm_tree_node(t_env *env, struct nlist_64 *nlist, char *name)
{
	t_nmtree *new;

	if (!(new = (t_nmtree*)malloc(sizeof(t_nmtree))))
		return (NULL);
	new->name = name;
	new->nlist = nlist;
	new->left = NULL;
	new->right = NULL;
	new->env = env;
	return (new);
}

static void			nmtree_insert(t_nmtree **root, t_nmtree *new, int options,
									int (*cmpf)(t_nmtree *, t_nmtree *, int))
{
	int cmp_ret;

	if (!(*root))
	{
		*root = new;
		return ;
	}
	cmp_ret = (*cmpf)(*root, new, options);
	if (cmp_ret > 0)
		nmtree_insert(&((*root)->right), new, options, cmpf);
	else if (cmp_ret <= 0)
		nmtree_insert(&((*root)->left), new, options, cmpf);
}

static void			*get_insert_function(int options)
{
	int (*cmpf)(t_nmtree *, t_nmtree *, int);

	cmpf = alpha_order_compare;
	cmpf = options & NUM_OP ? num_order_compare : cmpf;
	cmpf = options & P_OP ? symbol_order_compare : cmpf;
	return (cmpf);
}

t_nmtree			*insert_symbols(t_env *env, t_btinfo *btinfo, int options)
{
	char				*name;
	t_nmtree			*new;
	struct nlist_64		*nlist;
	t_nmtree			*symbols_root;

	nlist = btinfo->nlist;
	symbols_root = NULL;
	while (btinfo->nsyms--)
	{
		if ((nlist->n_type & N_STAB) == 0)
		{
			name = &(btinfo->symtabstr[rev_bytes(env, nlist->n_un.n_strx)]);
			if (!(new = create_nm_tree_node(env, nlist, name)))
				return (NULL);
			nmtree_insert(&symbols_root, new,
							options, get_insert_function(options));
		}
		nlist = ft_incbyte(nlist, env->is_64 ? sizeof(*nlist) : sizeof(struct nlist));
	}
	return (symbols_root);
}

void				print_tree(t_nmtree *symbol,
							void (*print_function)(t_nmtree *))
{
	if (!symbol)
		return ;
	print_tree(symbol->left, print_function);
	print_function(symbol);
	print_tree(symbol->right, print_function);
}
