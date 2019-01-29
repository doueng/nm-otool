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

int				process_macho(uint8_t *bin, int options)
{
	t_env					*env;
	struct symtab_command	*symtab;
	t_btinfo				*btinfo;
	t_nmtree				*nmtree;

	if (!(env = get_env(bin)))
		return (-1);
	if (!(symtab = (struct symtab_command*)get_ldcmd(env, LC_SYMTAB)))
		return (1);
	if (!(btinfo = (t_btinfo*)get_btinfo(bin, symtab)))
		return (-1);
	if (!(nmtree = (t_nmtree*)insert_symbols(btinfo, options)))
		return (-1);
	print_tree(nmtree, print_standard);
	return (0);
}
