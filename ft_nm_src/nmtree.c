/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmtree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:07:42 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 18:26:39 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_nmtree		*create_nm_tree_node(t_env *env,
											struct nlist_64 *nlist,
											char *name)
{
	t_nmtree *new;

	if (!(new = (t_nmtree*)malloc(sizeof(t_nmtree))))
		return (ft_error(MALLOC_FAILED, __FILE__, __LINE__));
	new->name = name;
	new->nlist = nlist;
	new->left = NULL;
	new->right = NULL;
	new->env = env;
	return (new);
}

static void			nmtree_insert(t_nmtree **root, t_nmtree *new,
									int (*cmpf)(t_nmtree *, t_nmtree *))
{
	int cmp_ret;

	if (!(*root))
	{
		*root = new;
		return ;
	}
	cmp_ret = (*cmpf)(*root, new);
	if (cmp_ret > 0)
		nmtree_insert(&((*root)->right), new, cmpf);
	else if (cmp_ret <= 0)
		nmtree_insert(&((*root)->left), new, cmpf);
}

static void			*get_insert_function(int options)
{
	int (*cmpf)(t_nmtree *, t_nmtree *);

	cmpf = alpha_order_compare;
	cmpf = options & VAL_OP ? value_order_compare : cmpf;
	cmpf = options & SYM_OP ? symbol_order_compare : cmpf;
	return (cmpf);
}

t_nmtree			*insert_symbols(t_env *env, t_btinfo *btinfo)
{
	char				*name;
	t_nmtree			*new;
	struct nlist_64		*nlist;
	t_nmtree			*root;

	nlist = btinfo->nlist;
	root = NULL;
	while (btinfo->nsyms--)
	{
		if ((nlist->n_type & N_STAB) == 0)
		{
			if (!(name = incbytes_rev(env, btinfo->symtabstr,
													nlist->n_un.n_strx)))
				return (ft_error(INVALID_FILE, __FILE__, __LINE__));
			if (!*name)
				return (ft_error(INVALID_FILE, __FILE__, __LINE__));
			if (!(new = create_nm_tree_node(env, nlist, name)))
				return (NULL);
			nmtree_insert(&root, new, get_insert_function(env->options));
		}
		if (!(nlist = incbytes(env, nlist,
						env->is_64 ? sizeof(*nlist) : sizeof(struct nlist))))
			return (ft_error(CORRUPT_FILE, __FILE__, __LINE__));
	}
	return (root);
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
