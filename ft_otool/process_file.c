#include "ft_otool.h"

int			process_file(char *filename, int options)
{
	t_bin				*bin_struct;
	uint8_t				*bin;
	int					rv;

	if (NULL == (bin_struct = get_bin(filename)))
		return (-1);
	bin = bin_struct->head;
	if (is_archive(bin))
	{
		ft_printf("Archive : %s\n", filename);
		rv = (process_archive(bin, filename, options));
	}
	else
	{
		ft_printf("%s:\n", filename);
		rv = (process_macho(bin, options));
	}
	return (rv == -1 ? -1 : free_bin(bin_struct));
}
