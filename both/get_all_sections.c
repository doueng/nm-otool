#include "nm_otool.h"

static int			get_nsects(uint8_t *bin, struct load_command *all_ldcmds, int ncmds)
{
	int		nsects;

	nsects = 0;
	while (ncmds--)
	{
		if (all_ldcmds->cmd == LC_SEGMENT_64)
			nsects += ((struct segment_command_64*)all_ldcmds)->nsects;
		bin += all_ldcmds->cmdsize;
		all_ldcmds = ft_incbyte(all_ldcmds, all_ldcmds->cmdsize);
	}
	return (nsects);
}

struct section_64	*get_allsects(uint8_t *bin,
								  struct load_command *all_ldcmds,
								  int ncmds)
{
	int							nsects;
	struct section_64			*all_sections;
	struct section_64			*curr_section;
	struct segment_command_64	*seg_64;
	size_t						curr_sections_size;

	nsects = get_nsects(bin, all_ldcmds, ncmds);
	if (!(all_sections = (struct section_64*)malloc(nsects * sizeof(*all_sections))))
		return (NULL);
	curr_section = all_sections;
	while (ncmds--)
	{
		if (all_ldcmds->cmd == LC_SEGMENT_64)
		{
			seg_64 = (struct segment_command_64*)all_ldcmds;
			curr_sections_size = seg_64->nsects * sizeof(struct section_64);
			ft_memcpy(curr_section, seg_64 + 1, curr_sections_size);
			curr_section = ft_incbyte(curr_section, curr_sections_size);
		}
		bin += all_ldcmds->cmdsize;
		all_ldcmds = ft_incbyte(all_ldcmds, all_ldcmds->cmdsize);
	}
	return (all_sections);
}
