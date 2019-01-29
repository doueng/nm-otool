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

// static struct section_64	*get_text_section(struct section_64 *all_sections)
// {
// 	struct section_64 *text_section;

// 	text_section = NULL;
// 	while (all_sections && !text_section)
// 	{
// 		if (ft_strnequ(all_sections->segname, "__TEXT", 6)
// 			&& ft_strnequ(all_sections->sectname, "__text", 6))
// 			text_section = all_sections;
// 		all_sections++;
// 	}
// 	return (text_section);
// }

static struct section_64	*get_text_section(t_env *env)
{
	struct section_64	*text_section;
	int					ncmds;
	struct load_command	*cmd;
	uint8_t				*ldcmds;

	ncmds = env->macho->ncmds;
	ldcmds = (uint8_t*) env->ldcmds;
	text_section = NULL;
	while (--ncmds && !text_section)
	{
		cmd = (struct load_command*)ldcmds;
		if (cmd->cmd == LC_SEGMENT_64)
			if (ft_strnequ(((struct segment_command_64*)cmd)->segname, "__TEXT", 6))
				text_section = (struct section_64*)(ldcmds + sizeof(struct segment_command_64));
		ldcmds += cmd->cmdsize;
	}
	return (text_section);
}
int							process_macho(uint8_t *bin, int options)
{
	struct section_64		*text_section;
	t_env					*env;

	(void)&options; // fix
	if (!(env = get_env(bin)))
		return (-1);
	if (!(text_section = get_text_section(env)))
		return (-1);
	ft_printf("Contents of (__TEXT,__text) section\n");
	dump_memory(bin, text_section);
	free_env(env);
	return (0);
}
