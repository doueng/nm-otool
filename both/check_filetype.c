/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filetype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:25:34 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 16:17:16 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int	is_macho(uint8_t *bin)
{
	ft_printf("%llx\n", bin);
	ft_printf("%llx\n", FAT_MAGIC);
	return (*(uint32_t*)bin == MH_MAGIC_64);
}

int	is_archive(uint8_t *bin)
{
	return (0 == ft_memcmp(bin, ARMAG, SARMAG));
}

int is_fat(uint8_t *bin)
{
	ft_printf("%llx\n", bin);
	ft_printf("%llx\n", FAT_MAGIC);
	return (*(uint32_t*)bin == FAT_MAGIC_64);
}
