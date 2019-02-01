#include "nm_otool.h"

t_env				*get_env(t_env *env, uint8_t *bin)
{
	uint32_t				header;

	env->macho = (struct mach_header_64*)bin;
	env->bin.head = bin;
	header = *(uint32_t*)bin;
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
	bin += env->is_64 ? sizeof(struct mach_header_64) : sizeof(struct mach_header);
	env->ldcmds = (struct load_command*)bin;
	return (env);
}
