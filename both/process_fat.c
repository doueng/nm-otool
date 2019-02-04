#include "nm_otool.h"

static int		process_arch(t_env *env,
							 t_env *fat_env,
							 void *arch,
							 int options)
{
	env->macho = fat_env->is_64
		? incbytes_rev(fat_env, env->filehead, ((struct fat_arch_64*)arch)->offset)
		: incbytes_rev(fat_env, env->filehead, ((struct fat_arch*)arch)->offset);
	if (!env->macho)
		return (ft_error_one(CORRUPT_FILE, __FILE__, __LINE__));
	if (!(env = update_env(env)))
		return (-1);
	if (-1 == process_macho(env, options))
		return (-1);
	return (0);
}

static int		process_all_archs(t_env *env,
								  t_env *fat_env,
								  uint32_t num_archs,
								  int options)
{
	void *arch;

	arch = incbytes(fat_env, env->filehead, sizeof(struct fat_header));
	while (num_archs--)
	{
		if (-1 == (process_arch(env, fat_env, arch, options)))
			return (-1);
		arch = incbytes(fat_env, arch, fat_env->is_64
			? sizeof(struct fat_arch_64)
			: sizeof(struct fat_arch));
	}
	return (0);
}

static int		process_arch_X86_64(t_env *env,
									t_env *fat_env,
									uint32_t num_archs,
									int options)
{
	struct fat_arch *arch;

	arch = incbytes(fat_env, env->filehead, sizeof(struct fat_header));
	while (num_archs--)
	{
		if (rev_bytes(fat_env, arch->cputype) == CPU_TYPE_X86_64)
			return (process_arch(env, fat_env, arch, options));
		arch = incbytes(fat_env, arch, fat_env->is_64
			? sizeof(struct fat_arch_64)
			: sizeof(struct fat_arch));
	}
	return (1);
}

int				process_fat(t_env *env, int options)
{
	struct fat_header	hd;
	uint32_t			num_archs;
	t_env				fat_env;
	int					rv;

	ft_bzero(&fat_env, sizeof(t_env));
	ft_memcpy(&hd, env->filehead, sizeof(hd));
	num_archs = rev_bytes(env, hd.nfat_arch);
	ft_memcpy(&fat_env, env, sizeof(t_env));
	fat_env.rev_bytes = 1;
	fat_env.is_64 = hd.magic == FAT_MAGIC_64 || hd.magic == FAT_CIGAM_64;
	rv = process_arch_X86_64(env, &fat_env, num_archs, options);
	if (rv == 1)
		return (process_all_archs(env, &fat_env, num_archs, options));
	return (rv);
}
