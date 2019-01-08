#include "ft_otool.h"


static struct section_64	*get_tt_section(struct section_64 *all_sections)
{
	struct section_64 *tt_section;

	tt_section = NULL;
	while (all_sections && !tt_section)
	{
		if (ft_strequ(all_sections->segname, "__TEXT")
			&& ft_strequ(all_sections->sectname, "__text"))
			tt_section = all_sections;
		all_sections++;
	}
	return (tt_section);
}

int							process_macho(uint8_t *bin, int options)
{
	struct section_64		*tt_section;
	t_env					*env;

	ft_printf("hello\n");
	if (!(env = get_env(bin)))
		return (-1);
	if (!(tt_section = get_tt_section(env->sections)))
		return (-1);
	ft_printf("Contents of (__TEXT,__text) section\n");
	dump_memory(bin + tt_section->offset, tt_section->size);
	free_env(env);
	return (0);
}
