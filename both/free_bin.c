#include "nm_otool.h"

int		free_bin(t_bin *bin)
{
	if (-1 == munmap(bin->head, bin->size))
		return (-1);
	free(bin);
	return (0);
}

void	free_env(t_env *env)
{
	free(env->sections);
	free(env);
}
