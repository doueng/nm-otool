#include "nm_otool.h"

t_env		*get_env(uint8_t *bin)
{
	t_env					*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	/* if (!(env->macho = (struct mach_header_64*)malloc(sizeof(struct mach_header_64)))) */
		/* return (NULL); */
	/* ft_memcpy(env->macho, bin, sizeof(struct mach_header_64)); */
	env->macho = (struct mach_header_64*)bin;
	/* if (!(env->ldcmds = (struct load_command*)malloc(env->macho->sizeofcmds))) */
		/* return (NULL); */
	bin += sizeof(struct mach_header_64);
	/* ft_memcpy(env->ldcmds, bin, env->macho->sizeofcmds); */
	env->ldcmds = (struct load_command*)bin;
	if (!(env->sections = get_allsects(bin, env->ldcmds, env->macho->ncmds)))
		return (NULL);
	return (env);
}
