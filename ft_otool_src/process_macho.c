/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_macho.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:25:31 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 19:02:35 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static struct section_64	*get_text_section64(t_env *env)
{
	struct section_64			*text_section;
	int							ncmds;
	struct load_command			*ldcmd;
	struct segment_command_64	*segcmd;

	ncmds = rev_bytes(env, env->macho->ncmds);
	ldcmd = env->ldcmds;
	text_section = NULL;
	while (--ncmds && !text_section)
	{
		segcmd = (struct segment_command_64*)ldcmd;
		if (rev_bytes(env, ldcmd->cmd) == LC_SEGMENT_64 && segcmd->filesize > 0)
		{
			text_section = (struct section_64*)(++segcmd);
			if (text_section->size <= 0
						|| ft_strcmp(text_section->sectname, "__text"))
				return (0);
			return (text_section);
		}
		if (!(ldcmd = incbytes_rev(env, ldcmd, ldcmd->cmdsize)))
			return (NULL);
	}
	return (text_section);
}

static struct section		*get_text_section(t_env *env)
{
	struct section				*text_section;
	int							ncmds;
	struct load_command			*ldcmd;
	struct segment_command		*segcmd;

	ncmds = rev_bytes(env, env->macho->ncmds);
	ldcmd = env->ldcmds;
	text_section = NULL;
	while (--ncmds && !text_section)
	{
		segcmd = (struct segment_command*)ldcmd;
		if (rev_bytes(env, ldcmd->cmd) == LC_SEGMENT && segcmd->filesize > 0)
		{
			text_section = (struct section*)(++segcmd);
			if (text_section->size <= 0
					|| ft_strcmp(text_section->sectname, "__text"))
				return (0);
			return (text_section);
		}
		if (!(ldcmd = incbytes_rev(env, ldcmd, ldcmd->cmdsize)))
			return (NULL);
	}
	return (text_section);
}

int							process_macho(t_env *env)
{
	struct symtab_command	*symtab;

	if (!(symtab = checksymtab(env)))
		return (-1);
	if ((env->options & IS_FAT_OP) == 0)
		ft_printf("%s:\n", env->filename);
	ft_printf("Contents of (__TEXT,__text) section\n");
	if (env->is_64)
		return (dump_memory(env, get_text_section64(env)));
	return (dump_memory(env, get_text_section(env)));
}
