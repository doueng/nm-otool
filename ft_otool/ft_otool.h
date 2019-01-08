#ifndef __OTOOL_H_
#define __OTOOL_H_

#include "../both/nm_otool.h"

#define						DUMP_OP 0b1

void						dump_memory(uint8_t *mem, int mem_size);
int							process_file(char *filename, int options);
int							process_macho(uint8_t *bin, int options);

#endif // __OTOOL_H_
