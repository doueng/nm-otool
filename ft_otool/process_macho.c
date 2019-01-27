/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_macho.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:25:31 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 15:29:25 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static struct section_64	*get_text_section(struct section_64 *all_sections)
{
	struct section_64 *text_section;

	text_section = NULL;
	while (all_sections && !text_section)
	{
		if (ft_strequ(all_sections->segname, "__TEXT")
			&& ft_strequ(all_sections->sectname, "__text"))
			text_section = all_sections;
		all_sections++;
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
	if (!(text_section = get_text_section(env->sections)))
		return (-1);
	ft_printf("Contents of (__TEXT,__text) section\n");
	dump_memory(bin, text_section);
	free_env(env);
	return (0);
}
