/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_archive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:05:00 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 16:07:30 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static uint8_t	*move_past_ar_hdr(uint8_t *bin)
{
	struct ar_hdr *hdr;

	hdr = (struct ar_hdr*)bin;
	if (0 == ft_memcmp(hdr->ar_name, AR_EFMT1, ft_strlen(AR_EFMT1)))
		bin += ft_atoi(hdr->ar_name + 3);
	bin += sizeof(struct ar_hdr);
	return (bin);
}

static long		get_num_ranlibs(uint8_t *bin)
{
	struct ar_hdr *hdr;

	hdr = (struct ar_hdr*)bin;
	if (0 == ft_memcmp(hdr->ar_name, AR_EFMT1, ft_strlen(AR_EFMT1)))
		bin += ft_atoi(hdr->ar_name + 3);
	bin += sizeof(struct ar_hdr);
	return (*((long*)bin) / sizeof(struct ranlib));
}

int				process_archive(t_env *env, char *archive_name, int options)
{
	int						num_ranlib;
	char					*filename;
	uint8_t					*bin;

	bin = env->filehead;
	bin = incbytes(env, bin, SARMAG);
	num_ranlib = get_num_ranlibs(bin);
	ft_printf("%d\n", num_ranlib);
	bin += ft_atoi((((struct ar_hdr*)bin)->ar_size));
	bin += sizeof(struct ar_hdr);
	while (*bin == '\n')
		bin++;
	while (*(uint32_t*)(move_past_ar_hdr(bin)) == MH_MAGIC_64)
	{
		while (*bin == '\n')
			bin++;
		if (!(filename = get_filename(bin)))
			return (-1);
		ft_printf("\n%s(%s):\n", archive_name, filename);
		free(filename);
		env->filehead = move_past_ar_hdr(bin);
		if (-1 == process_macho(env, options))
			return (-1);
		bin += ft_atoi((((struct ar_hdr*)bin)->ar_size));
		bin += sizeof(struct ar_hdr);
	}
	return (0);
}
