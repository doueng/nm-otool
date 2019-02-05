/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:07:57 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 18:28:59 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int64_t	print4bytes(t_env *env, uint8_t *mem, int64_t mem_size,
																int cputype)
{
	uint32_t	print_mem;
	int			i;

	print_mem =
			env->rev_bytes ? rev_bytes32(*(uint32_t*)mem) : (*(uint32_t*)mem);
	mem = (uint8_t*)&print_mem;
	i = 0;
	while (i++ < 4 && mem_size-- > 0)
	{
		if (cputype == 18 || cputype == 12 || cputype == 16777228)
			ft_printf("%02x%s", *mem, i % 4 ? "" : " ");
		else
			ft_printf("%02x ", *mem);
		mem++;
	}
	return (mem_size);
}

static void		dump32(t_env *env, struct section *text_section)
{
	uint32_t	pos;
	int64_t		mem_size;
	uint32_t	*mem;
	cpu_type_t	cputype;

	cputype = rev_bytes(env, env->macho->cputype);
	pos = rev_bytes(env, text_section->addr);
	mem = incbytes_rev(env, env->macho, text_section->offset);
	mem_size = rev_bytes(env, text_section->size);
	if (cputype == 18 || cputype == 12 || cputype == 16777228)
		env->rev_bytes = !env->rev_bytes;
	while (mem_size > 0)
	{
		ft_printf("%08x\t", pos);
		mem_size = print4bytes(env, (uint8_t*)mem++, mem_size, cputype);
		mem_size = print4bytes(env, (uint8_t*)mem++, mem_size, cputype);
		mem_size = print4bytes(env, (uint8_t*)mem++, mem_size, cputype);
		mem_size = print4bytes(env, (uint8_t*)mem++, mem_size, cputype);
		pos += 16;
		ft_putchar('\n');
	}
}

static void		dump64(t_env *env, struct section_64 *text_section)
{
	uint64_t	pos;
	int64_t		mem_size;
	uint32_t	*mem;
	cpu_type_t	cputype;

	cputype = rev_bytes(env, env->macho->cputype);
	pos = rev_bytes(env, text_section->addr);
	mem = incbytes(env, env->macho, env->rev_bytes
						? rev_bytes(env, text_section->offset)
						: text_section->offset);
	mem_size = rev_bytes(env, text_section->size);
	if (cputype == 18 || cputype == 12 || cputype == 16777228)
		env->rev_bytes = !env->rev_bytes;
	while (mem_size > 0)
	{
		ft_printf("%016llx\t", pos);
		mem_size = print4bytes(env, (uint8_t*)mem++, mem_size, cputype);
		mem_size = print4bytes(env, (uint8_t*)mem++, mem_size, cputype);
		mem_size = print4bytes(env, (uint8_t*)mem++, mem_size, cputype);
		mem_size = print4bytes(env, (uint8_t*)mem++, mem_size, cputype);
		pos += 16;
		ft_putchar('\n');
	}
}

int				dump_memory(t_env *env, void *text_section)
{
	if (!text_section)
		return (0);
	if (env->is_64)
		dump64(env, text_section);
	else
		dump32(env, text_section);
	return (0);
}
