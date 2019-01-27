#include "ft_otool.h"

void		dump_memory(uint8_t *mem, struct section_64 *text_section)
{
	uint64_t	pos;
	int			i;
	int64_t	mem_size;

	pos = text_section->addr;
	mem += text_section->offset;
	mem_size = text_section->size;
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
