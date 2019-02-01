/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:07:57 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/28 19:28:00 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	dump64(t_env *env, struct section_64 *text_section)
{
	uint64_t	pos;
	int			i;
	int64_t		mem_size;
	uint8_t		*mem;

	mem = env->bin.head;
	pos = rev_bytes(env, text_section->addr);
	mem += rev_bytes(env, text_section->offset);
	mem_size = rev_bytes(env, text_section->size);
	while (mem_size >= 0)
	{
		ft_printf("%016llx\t", pos);
		i = 0;
		while (i++ < 16 && mem_size--)
			ft_printf("%02x ", *mem++);
		pos += 16;
		ft_putchar('\n');
	}
}

static void	dump32(t_env *env, struct section *text_section)
{
	uint32_t	pos;
	int			i;
	int32_t		mem_size;
	uint8_t		*mem;

	mem = env->bin.head;
	pos = rev_bytes(env, text_section->addr);
	mem += rev_bytes(env, text_section->offset);
	mem_size = rev_bytes(env, text_section->size);
	while (mem_size >= 0)
	{
		ft_printf("%08x\t", pos);
		i = 0;
		while (i++ < 16 && mem_size--)
			if  (18 == rev_bytes(env, env->macho->cputype))
				ft_printf("%02x%s", *mem++, i % 4 == 0 ? " " : "");
			else
				ft_printf("%02x ", *mem++);
		pos += 16;
		ft_putchar('\n');
	}
}

int			dump_memory(t_env *env, void *text_section)
{
	if (!text_section)
		return (-1);
	if (env->is_64)
		dump64(env, text_section);
	else
		dump32(env, text_section);
	return (0);
}
