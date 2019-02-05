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


t_btinfo			*get_btinfo(t_env *env, struct symtab_command *symtab)
{
	t_btinfo	*info;
	void		*bin;

	bin = env->macho;
	if (!(info = (t_btinfo*)ft_memalloc(sizeof(t_btinfo))))
		return (ft_error(MALLOC_FAILED, __FILE__, __LINE__));
	if (!(info->nlist = incbytes_rev(env, bin, symtab->symoff)))
		return (ft_error(CORRUPT_FILE, __FILE__, __LINE__));
	if (!(info->symtabstr = incbytes_rev(env, bin, symtab->stroff)))
		return (ft_error(CORRUPT_FILE, __FILE__, __LINE__));
	info->nsyms = rev_bytes(env, symtab->nsyms);
	return (info);
}
