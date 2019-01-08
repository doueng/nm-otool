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

int				process_archive(uint8_t *bin, char *archive_name, int options)
{
	int						num_ranlib;
	char					*filename;

	bin += ft_strlen(ARMAG);
	num_ranlib = get_num_ranlibs(bin);
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
		if (-1 == process_macho(move_past_ar_hdr(bin), options))
			return (-1);
		bin += ft_atoi((((struct ar_hdr*)bin)->ar_size));
		bin += sizeof(struct ar_hdr);
	}
	return (0);
}
