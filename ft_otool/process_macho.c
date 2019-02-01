/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_macho.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:25:31 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/28 19:29:16 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static struct section_64	*get_text_section64(t_env *env)
{
	struct section_64	*text_section;
	int					ncmds;
	struct load_command	*cmd;
	uint8_t				*ldcmds;

	ncmds = rev_bytes(env, env->macho->ncmds);
	ldcmds = (uint8_t*) env->ldcmds;
	text_section = NULL;
	while (--ncmds && !text_section)
	{
		cmd = (struct load_command*)ldcmds;
		if (rev_bytes(env, cmd->cmd) == LC_SEGMENT_64)
			if (ft_strequ(((struct segment_command_64*)cmd)->segname, "__TEXT"))
				text_section = (struct section_64*)(ldcmds + sizeof(struct segment_command_64));
		ldcmds += rev_bytes(env, cmd->cmdsize);
	}
	return (text_section);
}


static struct section	*get_text_section(t_env *env)
{
	struct section		*text_section;
	int					ncmds;
	struct load_command	*cmd;
	uint8_t				*ldcmds;

	ncmds = rev_bytes(env, env->macho->ncmds);
	ldcmds = (uint8_t*) env->ldcmds;
	text_section = NULL;
	while (--ncmds && !text_section)
	{
		cmd = (struct load_command*)ldcmds;
		if (rev_bytes(env, cmd->cmd) == LC_SEGMENT)
			if (ft_strequ(((struct segment_command*)cmd)->segname, "__TEXT"))
				text_section = (struct section*)(ldcmds + sizeof(struct segment_command));
		ldcmds += rev_bytes(env, cmd->cmdsize);
	}
	return (text_section);
}

int							process_macho(t_env *env, int options)
{
	(void)&options; // fix
	ft_printf("Contents of (__TEXT,__text) section\n");
	if (env->is_64)
		return (dump_memory(env, get_text_section64(env)));
	return (dump_memory(env, get_text_section(env)));
}
