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

static char			sectname_to_char(char *sectname)
{
	if (ft_strequ(sectname, "__text"))
		return ('T');
	else if (ft_strequ(sectname, "__data"))
		return ('D');
	else if (ft_strequ(sectname, "__bss"))
		return ('B');
	else
		return ('S');
}

static char			get_section(void *first_section, int64_t sect_num, int is_64)
{
	struct section_64	*sections_64;
	struct section		*sections;
	char				*sectname;

	if (is_64)
		sections_64 = (struct section_64*)first_section + sect_num - 1;
	else
		sections = (struct section*)first_section + sect_num - 1;
	sectname = is_64 ? sections_64->sectname : sections->sectname;
	return (sectname_to_char(sectname));
}

static char			get_section_letter64(t_env *env, int64_t sect_num, char letter)
{
	struct load_command			*ldcmd;
	struct segment_command_64	*segcmd;
	uint32_t					ncmds;

	ldcmd = env->ldcmds;
	ncmds = rev_bytes(env, env->macho->ncmds);
	while (ncmds-- && sect_num > 0)
	{
		if (rev_bytes(env, ldcmd->cmd) == LC_SEGMENT_64)
		{
			segcmd = (struct segment_command_64*)ldcmd;
			if (0 > (sect_num - segcmd->nsects))
				return (get_section(incbytes(env, segcmd, sizeof(struct segment_command_64)), sect_num, 64));
			sect_num -= segcmd->nsects;
		}
		ldcmd = incbytes_rev(env, ldcmd, ldcmd->cmdsize);
	}
	return (letter);
}

static char			get_section_letter(t_env *env, int64_t sect_num, char letter)
{
	struct load_command		*ldcmd;
	struct segment_command	*segcmd;
	uint32_t				ncmds;

	ldcmd = env->ldcmds;
	ncmds = rev_bytes(env, env->macho->ncmds);
	while (ncmds-- && sect_num > 0)
	{
		if (rev_bytes(env, ldcmd->cmd) == LC_SEGMENT)
		{
			segcmd = (struct segment_command*)ldcmd;
			if (0 > (sect_num - segcmd->nsects))
				return (get_section(incbytes(env, segcmd, sizeof(struct segment_command)), sect_num, 0));
			sect_num -= segcmd->nsects;
		}
		ldcmd = incbytes_rev(env, ldcmd, ldcmd->cmdsize);
	}
	return (letter);
}

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
	if (symbol->env->is_64)
		letter = get_section_letter64(symbol->env, nsect, letter);
	else
		letter = get_section_letter(symbol->env, nsect, letter);
	if (type == N_UNDF  && nlist->n_type & N_EXT)
		letter = 'C';
	return (nlist->n_type & N_EXT ? letter : letter | 0x20);
}

void				print_standard(t_nmtree *symbol)
{
	struct nlist_64	*nlist;
	t_env			*env;

	env = symbol->env;
	nlist = symbol->nlist;
	if (symbol->env->is_64)
	{
		if (nlist->n_value == 0 && nlist->n_type == N_EXT)
			ft_printf("%16c U %s\n", ' ', symbol->name);
		else
			ft_printf("%016llx %c %s\n", rev_bytes(env, nlist->n_value), get_type_letter(symbol),
						symbol->name);
	}
	else
	{
		if ((uint32_t)nlist->n_value == 0 && nlist->n_type == N_EXT)
			ft_printf("%8c U %s\n", ' ', symbol->name);
		else
			ft_printf("%08x %c %s\n", rev_bytes(env, nlist->n_value), get_type_letter(symbol),
						symbol->name);
	}
}
