/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 18:05:30 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 18:26:02 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static int		process_arch(t_env *env,
							t_env *fat_env,
							void *arch)
{
	void *filehead;

	filehead = env->filehead;
	env->macho = fat_env->is_64
		? incbytes_rev(fat_env, filehead, ((struct fat_arch_64*)arch)->offset)
		: incbytes_rev(fat_env, filehead, ((struct fat_arch*)arch)->offset);
	if (!env->macho)
		return (ft_error_one(CORRUPT_FILE, __FILE__, __LINE__));
	if (!(env = update_env(env)))
		return (-1);
	if (-1 == process_macho(env))
		return (-1);
	return (0);
}

static char		*print_cpuname(t_env *env, void *arch)
{
	uint32_t	cpu;
	char		*cpu_name;
	char		*format_str;

	format_str = env->is_nm
		? "\n%s (for architecture %s):\n"
		: "%s (architecture %s):\n";
	cpu = ((struct fat_arch*)arch)->cputype & CPU_ARCH_MASK;
	cpu_name = "";
	cpu_name = cpu == 7 || cpu == rev_bytes32(7) ? "i386" : cpu_name;
	cpu_name = cpu == CPU_TYPE_ARM || cpu == rev_bytes32(CPU_TYPE_ARM)
		? "arm" : cpu_name;
	cpu_name = cpu == 18 || cpu == rev_bytes32(18) ? "ppc" : cpu_name;
	cpu_name = cpu == CPU_TYPE_POWERPC || cpu == rev_bytes32(CPU_TYPE_POWERPC)
		? "ppc" : cpu_name;
	ft_printf(format_str, env->filename, cpu_name);
	return (cpu_name);
}

static int		process_all_archs(t_env *env,
								t_env *fat_env,
								uint32_t num_archs)
{
	void	*arch;
	int		rv;
	size_t	struct_size;

	rv = 0;
	arch = incbytes(fat_env, env->filehead, sizeof(struct fat_header));
	struct_size = fat_env->is_64
						? sizeof(struct fat_arch_64)
						: sizeof(struct fat_arch);
	while (num_archs--)
	{
		print_cpuname(env, arch);
		if (-1 == process_arch(env, fat_env, arch))
			rv = -1;
		if (!(arch = incbytes(fat_env, arch, struct_size)))
			return (ft_error_one(INVALID_FILE, __FILE__, __LINE__));
	}
	return (rv);
}

static int		process_arch_x86_64(t_env *env,
									t_env *fat_env,
									uint32_t num_archs)
{
	struct fat_arch *arch;

	arch = incbytes(fat_env, env->filehead, sizeof(struct fat_header));
	while (num_archs--)
	{
		if (rev_bytes(fat_env, arch->cputype) == CPU_TYPE_X86_64)
			return (process_arch(env, fat_env, arch));
		if (!(arch = incbytes(fat_env, arch, fat_env->is_64
									? sizeof(struct fat_arch_64)
									: sizeof(struct fat_arch))))
			return (ft_error_one(INVALID_FILE, __FILE__, __LINE__));
	}
	return (1);
}

int				process_fat(t_env *env)
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
	rv = process_arch_x86_64(env, &fat_env, num_archs);
	env->options |= IS_FAT_OP;
	if (rv == 1)
		return (process_all_archs(env, &fat_env, num_archs));
	return (rv);
}
