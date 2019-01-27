#include "ft_nm.h"

int			invalid_file(char *filename)
{
	/* /Library/Developer/CommandLineTools/usr/bin/nm: ft_nm.dSYM: Is a directory. */
	struct stat st;
	int			fd;

	if (-1 == (fd = (open(filename, O_RDONLY))))
		return (-1);
	if (-1 == fstat(fd, &st))
		return (-1);
	if (st.st_mode & S_IFDIR)
	{
		ft_printf("ft_nm: %s: Is a directory.\n", filename);
		return (-1);
	}
	return (0);
}

int			invalid_file_type(char *filename)
{
	ft_printf("ft_nm: %s: The file was not recognized as a valid object file\n", filename);
	return (-1);
}

int			process_file(char *filename, int options)
{
	t_bin				*bin_struct;
	uint8_t				*bin;
	int					rv;

	if (-1 == invalid_file(filename))
		return (-1);
	if (NULL == (bin_struct = get_bin(filename)))
		return (-1);
	bin = bin_struct->head;
	if (is_archive(bin))
		rv = process_archive(bin, filename, options);
	else if (is_macho(bin))
		rv = process_macho(bin, options);
	else
		rv = invalid_file_type(filename);
	free_bin(bin_struct);
	return (rv);
}
