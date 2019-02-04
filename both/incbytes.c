#include "nm_otool.h"

void	*incbytes_rev(t_env *env, void *mem, size_t inc_size)
{
	if (!mem)
		return (NULL);
	if (((void*)env->macho + env->filesize) < (mem + (rev_bytes(env, inc_size))))
		return (NULL);
	return (mem + (rev_bytes(env, inc_size)));
}

void	*incbytes(t_env *env, void *mem, size_t inc_size)
{
	if (!mem)
		return (NULL);
	if (((void*)env->macho + env->filesize) < (mem + inc_size))
		return (NULL);
	return (mem + inc_size);
}
