/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:27:57 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 18:24:46 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_OTOOL_H_
#define __NM_OTOOL_H_

#include <stdlib.h>
#include <mach-o/loader.h>
#include <mach-o/swap.h>
#include <ar.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "../libft/libft.h"

# define error_msg(error) error, __FILE__, __LINE__

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

typedef struct					s_env
{
	struct mach_header_64		*macho;
	struct load_command			*ldcmds;
	char						is_64;
	char						rev_bytes;
	char						*filename;
	size_t						filesize;
	void						*filehead;
}								t_env;

t_env							*update_env(t_env *env);
void							*ft_error(int error, char *file, int line);
int								ft_error_one(int error, char *file, int line);
void							*incbytes_rev(t_env *env, void *mem, size_t inc_size);
void							*incbytes(t_env *env, void *mem, size_t inc_size);
t_env							*get_env(char *filename);
uint64_t						rev_bytes(t_env *env, uint64_t bytes);
int								process_fat(t_env *env, int options);
int								is_fat(uint8_t *bin);
int 							is_macho(uint8_t *bin);
void							free_env(t_env *env);
int								process_macho(t_env *env, int options);;
int								process_archive(t_env *env, char *archive_name,
												int options);
int								is_archive(uint8_t *bin);
struct section_64				*get_allsects(uint8_t *bin,
											struct load_command *all_ldcmds,
											int ncmds);
char							*get_filename(uint8_t *bin);

#endif
