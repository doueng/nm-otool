#include "ft_otool.h"

void		dump_memory(uint8_t *mem, int mem_size)
{
	size_t	pos;
	int		i;

	pos = 0;
	while (mem_size > 0)
	{
		ft_printf("%016x\t", pos);
		i = 0;
		while (i++ < 16 && mem_size--)
			ft_printf("%02x ", *mem++);
		pos += 16;
		ft_putchar('\n');
	}
}
