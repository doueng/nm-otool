/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:06:42 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 19:13:27 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

struct load_command	*get_ldcmd(t_env *env, uint32_t cmd)
{
	struct load_command *ldcmds;
	uint32_t			ncmds;

	ldcmds = env->ldcmds;
	ncmds = rev_bytes(env, env->macho->ncmds);
	while (ncmds--)
	{
		if (rev_bytes(env, ldcmds->cmd) == cmd)
			return (ldcmds);
		ldcmds = ft_incbyte(ldcmds, rev_bytes(env, ldcmds->cmdsize));
	}
	return (NULL);
}

t_btinfo			*get_btinfo(t_env *env, struct symtab_command *symtab)
{
	t_btinfo	*info;
	uint8_t		*bin;

	bin = env->bin.head;
	if (!(info = (t_btinfo*)ft_memalloc(sizeof(t_btinfo))))
		return (NULL);
	info->nlist = (struct nlist_64*) (bin + rev_bytes(env, symtab->symoff));
	info->symtabstr = (char *) (bin + rev_bytes(env, symtab->stroff));
	info->nsyms = rev_bytes(env, symtab->nsyms);
	return (info);
}

