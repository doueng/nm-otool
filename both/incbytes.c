#include "nm_otool.h"

void	*incbytes_rev(t_env *env, void *mem, size_t inc_size)
{
	if (((void*)env->macho + env->bin.size) < (mem + (rev_bytes(env, inc_size))))
		return (NULL);
	return (mem + (rev_bytes(env, inc_size)));
}

void	*incbytes(t_env *env, void *mem, size_t inc_size)
{
	if (((void*)env->macho + env->bin.size) < (mem + inc_size))
		return (NULL);
	return (mem + inc_size);
}
