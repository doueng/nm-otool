#include "nm_otool.h"

t_bin		*get_bin(char *filename)
{
	t_bin		*bin;
	int			fd;
	struct stat	st;

	if (-1 == (fd = open(filename, O_RDONLY)))
		return (NULL);
	if (!(bin = (t_bin*)malloc(sizeof(t_bin))))
		return (NULL);
	if (-1 == fstat(fd, &st))
		return (NULL);
	bin->head = mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	bin->size = st.st_size;
	if (-1 == close(fd))
		return (NULL);
	return (MAP_FAILED == bin->head ? NULL : bin);
}
