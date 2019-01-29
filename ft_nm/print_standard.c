/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_standard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:13:02 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 16:49:46 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
/* #define N_UNDF  0x00            /\* undefined *\/ */
/* #define N_ABS   0x02            /\* absolute address *\/ */
#define N_TEXT  0x04            /* text segment */
#define N_DATA  0x06            /* data segment */
#define N_BSS   0x08            /* bss segment */
#define N_COMM  0x12            /* common reference */
#define N_FN    0x1e            /* file name */

/* #define N_EXT   0x01            /\* external (global) bit, OR'ed in *\/ */
/* #define N_TYPE  0x1e            /\* mask for all the type bits *\/ */
#define N_FORMAT        "%08x"  /* namelist value format; XXX */
/* #define N_STAB          0x0e0   /\* mask for debugger symbols -- stab(5) *\/ */

static char			get_type_letter(t_nmtree *symbol)
{
	char			letter;
	uint8_t			type;
	uint8_t			n_sect;
	struct nlist_64	*nlist;

	nlist = symbol->nlist;
	type = nlist->n_type & N_TYPE;
	type &= 0b11111110;
	n_sect = nlist->n_sect;
	letter = 'S';
	letter = type == N_UNDF ? 'U' : letter;
	letter = type == N_ABS ? 'A' : letter;
	letter = type == N_TEXT ? 'T' : letter;
	letter = type == N_DATA ? 'D' : letter;
	letter = type == N_BSS ? 'B' : letter;
	letter = type == N_COMM ? 'C' : letter;
	letter = type == N_FN ? 'F' : letter;
	return (nlist->n_type & N_EXT ? letter : letter | 0x20);
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
