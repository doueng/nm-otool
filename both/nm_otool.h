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
	struct section_64			*sections;
	struct load_command			*ldcmds;
	t_bin						*bin;
}								t_env;

int 							is_macho(uint8_t *bin);
void							free_env(t_env *env);
void							dump_memory(uint8_t *mem, int mem_size);
int								process_macho(uint8_t *bin, int options);;
int								process_archive(uint8_t *bin, char *archive_name, int options);
t_env							*get_env(uint8_t *bin);
int								is_archive(uint8_t *bin);
int								free_bin(t_bin *bin);
struct section_64				*get_allsects(uint8_t *bin,
											  struct load_command *all_ldcmds,
											  int ncmds);
t_bin							*get_bin(char *filename);
int								ft_error_one(char *error_text);
void							*ft_error(char *error_text);
char							*get_filename(uint8_t *bin);

#endif // __NM_OTOOL_H_
