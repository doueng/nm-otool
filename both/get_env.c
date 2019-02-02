#include "nm_otool.h"

static t_bin		*get_bin(char *filename)
{
	t_bin		*bin;
	int			fd;
	struct stat	st;

	if (-1 == (fd = open(filename, O_RDONLY)))
		return (ft_error(OPEN_FAILED, __FILE__, __LINE__));
	if (!(bin = (t_bin*)ft_memalloc(sizeof(t_bin))))
		return (ft_error(MALLOC_FAILED, __FILE__, __LINE__));
	if (-1 == fstat(fd, &st))
		return (ft_error(FSTAT_FAILED, __FILE__, __LINE__));
	bin->head = mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	bin->size = st.st_size;
	if (-1 == close(fd))
		return (ft_error(CLOSE_FAILED, __FILE__, __LINE__));
	if (MAP_FAILED == bin->head)
		return (ft_error(MMAP_FAILED, __FILE__, __LINE__));
	return (bin);
}

t_env				*get_env(char *filename)
{
	uint32_t				header;
	t_env					*env;
	t_bin					*bin_struct;

	if (NULL == (bin_struct = get_bin(filename)))
		return (NULL);
	if (!(env = (t_env*)ft_memalloc(sizeof(t_env))))
		return (ft_error(MALLOC_FAILED, __FILE__, __LINE__));
	env->macho = (struct mach_header_64*)bin_struct->head;
	ft_memcpy(&env->bin, bin_struct, sizeof(t_bin));
	env->filename = filename;
	header = env->macho->magic;
	env->is_64 = header == MH_MAGIC_64
		|| header == MH_CIGAM_64
		|| header == FAT_CIGAM_64
		|| header == FAT_MAGIC_64
		? 1 : 0;
	env->rev_bytes = header == MH_CIGAM
		|| header == MH_CIGAM_64
		|| header == FAT_CIGAM
		|| header == FAT_CIGAM_64
		? 1 : 0;
	env->ldcmds = (struct load_command*)(env->macho + 1);
	free(bin_struct);
	return (env);
}
