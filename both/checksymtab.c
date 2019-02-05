/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksymtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 18:05:49 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 18:08:49 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static struct load_command	*get_ldcmd(t_env *env, uint32_t cmd)
{
	struct load_command *ldcmds;
	uint32_t			ncmds;

	ldcmds = env->ldcmds;
	ncmds = rev_bytes(env, env->macho->ncmds);
	while (ncmds--)
	{
		if (rev_bytes(env, ldcmds->cmd) == cmd)
			return (ldcmds);
		if (!(ldcmds = incbytes_rev(env, ldcmds, ldcmds->cmdsize)))
			return (NULL);
	}
	return (NULL);
}

struct symtab_command		*checksymtab(t_env *env)
{
	struct symtab_command	*symtab;

	if (!(symtab = (struct symtab_command*)get_ldcmd(env, LC_SYMTAB)))
		return (ft_error(NO_SYMTAB, __FILE__, __LINE__));
	if (!(incbytes_rev(env,
						incbytes_rev(env, env->macho, symtab->strsize),
						symtab->stroff)))
		return (ft_error(INVALID_FILE, __FILE__, __LINE__));
	return (symtab);
}
