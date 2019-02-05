/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:27:57 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 19:06:49 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_OTOOL_H
# define __NM_OTOOL_H

# include <stdlib.h>
# include <mach-o/loader.h>
# include <mach-o/swap.h>
# include <ar.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include "../libft/libft.h"

enum
{
	CORRUPT_FILE,
	INVALID_FILE,
	FSTAT_FAILED,
	OPEN_FAILED,
	CLOSE_FAILED,
	MMAP_FAILED,
	NO_SYMTAB,
	INVALID_ARG,
	MALLOC_FAILED
};

# define NM_OP 0b1
# define VAL_OP 0b10
# define REV_OP 0b100
# define SYM_OP 0b1000


typedef struct					s_env
{
	struct mach_header_64		*macho;
	struct load_command			*ldcmds;
	char						is_64;
	char						rev_bytes;
	char						*filename;
	size_t						filesize;
	void						*filehead;
	int							options;
	char						is_nm;
}								t_env;

uint32_t						rev_bytes32(uint32_t bytes);
uint64_t						rev_bytes64(uint64_t bytes);
struct symtab_command			*checksymtab(t_env *env);
t_env							*update_env(t_env *env);
void							*ft_error(int error, char *file, int line);
int								ft_error_one(int error, char *file, int line);
void							*incbytes_rev(t_env *env, void *mem, size_t inc_size);
void							*incbytes(t_env *env, void *mem, size_t inc_size);
t_env							*get_env(char *filename, int options);
uint64_t						rev_bytes(t_env *env, uint64_t bytes);
int								process_fat(t_env *env);
int								is_fat(uint8_t *bin);
int 							is_macho(uint8_t *bin);
void							free_env(t_env *env);
int								process_macho(t_env *env);;
int								process_archive(t_env *env, char *archive_name);
int								is_archive(uint8_t *bin);
struct section_64				*get_allsects(uint8_t *bin,
											struct load_command *all_ldcmds,
											int ncmds);
char							*get_filename(uint8_t *bin);

#endif
