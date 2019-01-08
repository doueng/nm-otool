#include "nm_otool.h"

char		*get_filename(uint8_t *bin)
{
	char			*name;
	int				name_size;
	struct ar_hdr	*hdr;

	hdr = (struct ar_hdr*)bin;
	if (0 == ft_memcmp(hdr->ar_name, "#1/", 3))
	{
		name_size = ft_atoi(hdr->ar_name + 3);
		if (!(name = ft_strnew(name_size)))
			return (NULL);
		if (!(ft_memcpy(name, bin + sizeof(struct ar_hdr), name_size)))
			return (NULL);
	}
	else
	{
		if (!(name = ft_strnew(16)))
			return (NULL);
		ft_memcpy(name, hdr->ar_name, 16);
	}
	return (name);
}

/* char		*get_filename(int fd, struct ar_hdr *ar_header) */
/* { */
/* 	char	*name; */
/* 	int		name_size; */

/* 	if (0 == ft_memcmp(ar_header->ar_name, "#1/", 3)) */
/* 	{ */
/* 		name_size = ft_atoi(ar_header->ar_name + 3); */
/* 		if (!(name = ft_strnew(name_size))) */
/* 			return (NULL); */
/* 		if (-1 == read(fd, name, name_size)) */
/* 			return (NULL); */
/* 	} */
/* 	else */
/* 	{ */
/* 		if (!(name = ft_strnew(16))) */
/* 			return (NULL); */
/* 		ft_memcpy(name, ar_header->ar_name, 16); */
/* 	} */
/* 	return (name); */
/* } */
