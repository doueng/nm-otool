#include "nm_otool.h"

int is_macho(uint8_t *bin)
{
	return (*(uint32_t*)bin== MH_MAGIC_64);
}


int	is_archive(uint8_t *bin)
{
	return (0 == ft_memcmp(bin, ARMAG, SARMAG));
}

/* int	is_archive(char *filename) */
/* { */
/* 	int		fd; */
/* 	char	ar_magic[8]; */

/* 	if (-1 == (fd = open(filename, O_RDONLY))) */
/* 		return (-1); */
/* 	if (-1 == read(fd, ar_magic, 8)) */
/* 		return (-1); */
/* 	if (-1 == close(fd)) */
/* 		return (-1); */
/* 	return (ft_strnequ(ar_magic, ARMAG, 8) ? 1 : 0); */
/* } */
