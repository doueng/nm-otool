#include "ft_nm.h"

static char			get_type_letter(t_nmtree *symbol)
{
	char			letter;
	uint8_t			type;
	uint8_t			n_sect;
	struct nlist_64	*nlist;
	char			sect_name[17];

	nlist = symbol->nlist;
	type = nlist->n_type;
	n_sect = nlist->n_sect;
	letter = 'S';
	if (type == N_EXT)
		letter = 'C';
	else if (n_sect == NO_SECT)
		letter = type & N_ABS ? 'A' : letter;
	else if (n_sect > 0)
	{
		ft_memcpy(sect_name, symbol->sections[n_sect - 1].sectname, 16);
		letter = ft_strequ(sect_name, "__text") ? 'T' : letter;
		letter = ft_strequ(sect_name, "__data") ? 'D' : letter;
		ft_printf("hello\n");
	}
	return (type & N_EXT ? letter : letter | 0x20);
}

void				print_standard(t_nmtree *symbol)
{
	struct nlist_64	*nlist;

	nlist = symbol->nlist;
	if (nlist->n_value == 0 && nlist->n_type == N_EXT)
		ft_printf("%16c U %s\n", ' ', symbol->name);
	/* else if (nlist->n_type & N_EXT) */
	else if (nlist->n_type != 0x3c)
		ft_printf("%016llx %c %s\n", nlist->n_value, get_type_letter(symbol),
				  symbol->name);
}
