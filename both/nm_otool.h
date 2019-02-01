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

typedef struct					s_bin
{
	size_t						size;
	uint8_t						*head;
}								t_bin;

typedef struct					s_env
{
	struct mach_header_64		*macho;
	struct load_command			*ldcmds;
	char						is_64;
	char						rev_bytes;
	t_bin						bin;
}								t_env;

t_env							*get_env(t_env *env, uint8_t *bin);
uint64_t						rev_bytes(t_env *env, uint64_t bytes);
int								process_fat(t_env *env, int options);
int								is_fat(uint8_t *bin);
int 							is_macho(uint8_t *bin);
void							free_env(t_env *env);
int								process_macho(t_env *env, int options);;
int								process_archive(t_env *env, char *archive_name,
												int options);
t_env							*get_env(t_env *env, uint8_t *bin);
int								is_archive(uint8_t *bin);
int								free_bin(t_bin *bin);
struct section_64				*get_allsects(uint8_t *bin,
											struct load_command *all_ldcmds,
											int ncmds);
t_bin							*get_bin(char *filename);
int								ft_error_one(char *error_text);
void							*ft_error(char *error_text);
char							*get_filename(uint8_t *bin);

#endif
