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

void		dump_memory(uint8_t *mem, struct section_64 *text_section)
{
	uint64_t	pos;
	int			i;
	int64_t	mem_size;

	pos = text_section->addr;
	mem += text_section->offset;
	mem_size = text_section->size;
	ft_printf("offset %llx, size %zu\n", text_section->offset, text_section->size);
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
