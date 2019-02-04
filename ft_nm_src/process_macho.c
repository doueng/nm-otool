/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_macho.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:25:28 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 19:14:48 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		freetree(t_nmtree *root)
{
	if (!root)
		return ;
	freetree(root->left);
	freetree(root->right);
	free(root);
}

int				process_macho(t_env *env, int options)
{
	struct symtab_command	*symtab;
	t_btinfo				*btinfo;
	t_nmtree				*nmtree;

	if (!(symtab = (struct symtab_command*)get_ldcmd(env, LC_SYMTAB)))
		return (ft_error_one(NO_SYMTAB, __FILE__, __LINE__));
	if (!(btinfo = (t_btinfo*)get_btinfo(env, symtab)))
		return (-1);
	if (!(nmtree = (t_nmtree*)insert_symbols(env, btinfo, options)))
		return (-1);
	print_tree(nmtree, print_standard);
	free(btinfo);
	freetree(nmtree);
	return (0);
}
