/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_standard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:13:02 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 18:31:37 by dengstra         ###   ########.fr       */
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

static char			get_section(t_env *env, struct load_command *ldcmd,
								int64_t sect_index)
{
	char				*sectname;
	size_t				sectsize;
	size_t				segcmd_size;

	segcmd_size = env->is_64
		? sizeof(struct segment_command_64)
		: sizeof(struct segment_command);
	sect_index--;
	sectsize = env->is_64 ? sizeof(struct section_64) : sizeof(struct section);
	sectname = (char*)incbytes(env, ldcmd, segcmd_size) + sect_index * sectsize;
	return (sectname_to_char(sectname));
}

static char			get_section_letter(t_env *env, int64_t sect_index,
								char letter)
{
	struct load_command		*ldcmd;
	int64_t					nsects;

	if (sect_index <= 0)
		return (letter);
	ldcmd = env->ldcmds;
	while (rev_bytes(env, ldcmd->cmd) == LC_SEGMENT
			|| rev_bytes(env, ldcmd->cmd) == LC_SEGMENT_64)
	{
		nsects = env->is_64
			? rev_bytes(env, ((struct segment_command_64*)ldcmd)->nsects)
			: rev_bytes(env, ((struct segment_command*)ldcmd)->nsects);
		if (sect_index <= nsects)
			return (get_section(env, ldcmd, sect_index));
		sect_index -= nsects;
		ldcmd = incbytes_rev(env, ldcmd, ldcmd->cmdsize);
	}
	return (letter);
}

static char			get_type_letter(t_nmtree *symbol)
{
	char			letter;
	uint8_t			type;
	struct nlist_64	*nlist;

	nlist = symbol->nlist;
	type = nlist->n_type & N_TYPE;
	letter = 'S';
	letter = get_section_letter(symbol->env, nlist->n_sect, letter);
	if (type == N_UNDF  && nlist->n_type & N_EXT)
		letter = 'C';
	letter = type == N_UNDF ? 'U' : letter;
	letter = type == N_ABS ? 'A' : letter;
	letter = type == N_INDR ? 'I' : letter;
	return (nlist->n_type & N_EXT ? letter : letter | 0x20);
}

void			print_standard(t_nmtree *symbol)
{
	struct nlist_64	*nlist;
	t_env			*env;
	char			type_letter;

	env = symbol->env;
	nlist = symbol->nlist;
	type_letter = get_type_letter(symbol);
	if (symbol->env->is_64)
	{
		nlist->n_value == 0 && nlist->n_type == N_EXT
			? ft_printf("%16c U %s\n", ' ', symbol->name)
			: ft_printf("%016llx %c %s\n",
					rev_bytes(env, nlist->n_value),
					type_letter,
					symbol->name);
	}
	else
	{
		(uint32_t)nlist->n_value == 0 && nlist->n_type == N_EXT
			? ft_printf("%8c U %s\n", ' ', symbol->name)
			: ft_printf("%08x %c %s\n",
					rev_bytes(env, nlist->n_value),
					type_letter,
					symbol->name);
	}
}
