#include "nm_otool.h"

static int          process_fat64(t_env *env,
                                  t_env *fat_env,
                                  uint32_t num_archs,
                                  int options)
{
    struct fat_arch_64  *arch;
    uint8_t             *file_hd;

    fat_env->is_64 = 1;
    file_hd = env->bin.head;
    arch = (struct fat_arch_64*)(env->bin.head + sizeof(sizeof(struct fat_header)));
    while (num_archs--)
    {
        if (!(env = get_env(env, file_hd + rev_bytes(fat_env, arch->offset))))
            return (-1);
        if (-1 == process_macho(env, options))
            return (-1);
        arch++;
    }
    return (0);
}

static int          process_fat32(t_env *env,
                                  t_env *fat_env,
                                  uint32_t num_archs,
                                  int options)
{
    struct fat_arch     *arch;
    uint8_t             *file_hd;

    fat_env->is_64 = 0;
    file_hd = env->bin.head;
    arch = (struct fat_arch*)(env->bin.head + sizeof(struct fat_header));
    while (num_archs--)
    {
        if (!(env = get_env(env, file_hd + rev_bytes(fat_env, arch->offset))))
            return (-1);
        if (-1 == process_macho(env, options))
            return (-1);
        arch++;
    }
    return (0);
}

int				process_fat(t_env *env, int options)
{
    struct fat_header   hd;
    uint32_t            num_archs;
    t_env               fat_env;

    ft_bzero(&fat_env, sizeof(t_env));
    ft_memcpy(&hd, env->bin.head, sizeof(hd));
    num_archs = rev_bytes(env, hd.nfat_arch);
    fat_env.rev_bytes = 1;
    if (hd.magic == FAT_MAGIC_64)
        return (process_fat64(env, &fat_env, num_archs, options));
    return (process_fat32(env, &fat_env, num_archs, options));
}

/* typedef struct					s_env */
/* { */
/* 	struct mach_header_64		*macho; */
/* 	struct load_command			*ldcmds; */
/* 	char						is_64; */
/* 	char						rev_bytes; */
/* 	t_bin						bin; */
/* }								t_env; */
/* #define FAT_MAGIC_64    0xcafebabf */
/* #define FAT_CIGAM_64    0xbfbafeca      /\* NXSwapLong(FAT_MAGIC_64) *\/ */

/* #define FAT_MAGIC       0xcafebabe */
/* #define FAT_CIGAM       0xbebafeca      /\* NXSwapLong(FAT_MAGIC) *\/ */

/* struct fat_header { */
/*         uint32_t        magic;          /\* FAT_MAGIC or FAT_MAGIC_64 *\/ */
/*         uint32_t        nfat_arch;      /\* number of structs that follow *\/ */
/* }; */

/* struct fat_arch { */
/*         cpu_type_t      cputype;        /\* cpu specifier (int) *\/ */
/*         cpu_subtype_t   cpusubtype;     /\* machine specifier (int) *\/ */
/*         uint32_t        offset;         /\* file offset to this object file *\/ */
/*         uint32_t        size;           /\* size of this object file *\/ */
/*         uint32_t        align;          /\* alignment as a power of 2 *\/ */
/* }; */

/* struct fat_arch_64 { */
/*         cpu_type_t      cputype;        /\* cpu specifier (int) *\/ */
/*         cpu_subtype_t   cpusubtype;     /\* machine specifier (int) *\/ */
/*         uint64_t        offset;         /\* file offset to this object file *\/ */
/*         uint64_t        size;           /\* size of this object file *\/ */
/*         uint32_t        align;          /\* alignment as a power of 2 *\/ */
/*         uint32_t        reserved;       /\* reserved *\/ */
/* }; */
