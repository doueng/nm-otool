#include "nm_otool.h"

static int		process_fat64(t_env *env,
									t_env *fat_env,
									uint32_t num_archs,
									int options)
{
	struct fat_arch_64	*arch;
	uint8_t				*file_hd;

	fat_env->is_64 = 1;
	file_hd = env->filehead;
	arch = incbytes(fat_env, file_hd, sizeof(struct fat_header));
	while (num_archs--)
	{
		env->macho = incbytes_rev(fat_env, file_hd, arch->offset);
		if (!env->macho)
			return (ft_error_one(CORRUPT_FILE, __FILE__, __LINE__));
		if (!(env = update_env(env)))
			return (-1);
		if (-1 == process_macho(env, options))
			return (-1);
		arch++;
	}
	return (0);
}


static int		process_fat32(t_env *env,
									t_env *fat_env,
									uint32_t num_archs,
									int options)
{
	struct fat_arch		*arch;
	void				*file_hd;

	fat_env->is_64 = 0;
	file_hd = env->filehead;
	arch = incbytes(fat_env, file_hd, sizeof(struct fat_header));
	while (num_archs--)
	{
		env->macho = incbytes_rev(fat_env, file_hd, arch->offset);
		if (!env->macho)
			return (ft_error_one(CORRUPT_FILE, __FILE__, __LINE__));
		if (!(env = update_env(env)))
			return (-1);
		if (-1 == process_macho(env, options))
			return (-1);
		arch++;
	}
	return (0);
}

int				process_fat(t_env *env, int options)
{
	struct fat_header	hd;
	uint32_t			num_archs;
	t_env				fat_env;

	ft_bzero(&fat_env, sizeof(t_env));
	ft_memcpy(&hd, env->filehead, sizeof(hd));
	num_archs = rev_bytes(env, hd.nfat_arch);
	ft_memcpy(&fat_env, env, sizeof(t_env));
	fat_env.rev_bytes = 1;
	if (hd.magic == FAT_MAGIC_64 || hd.magic == FAT_CIGAM_64)
		return (process_fat64(env, &fat_env, num_archs, options));
	return (process_fat32(env, &fat_env, num_archs, options));
}
