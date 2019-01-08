#include "ft_nm.h"

char				*get_symtabstr(uint8_t *bin, struct symtab_command *symtab)
{
	char	*symtabstr;

	if (!(symtabstr = ft_strnew(symtab->strsize)))
		return (NULL);
	bin += symtab->stroff;
	if (!(ft_memcpy(symtabstr, bin, symtab->strsize)))
		return (NULL);
	return (symtabstr);
}

struct nlist_64		*get_nlist(uint8_t *bin, struct symtab_command *symtab)
{
	struct nlist_64 *nlist;
	size_t			nlist_size;

	nlist_size = sizeof(struct nlist_64) * symtab->nsyms;
	if (!(nlist = (struct nlist_64*)malloc(nlist_size)))
		return (NULL);
	bin += symtab->symoff;
	if (!(ft_memcpy(nlist, bin, nlist_size)))
		return (NULL);
	return (nlist);
}

struct load_command *get_ldcmd(t_env* env, uint32_t cmd)
{
	struct load_command *ldcmds;
	uint32_t			ncmds;

	ldcmds = env->ldcmds;
	ncmds = env->macho->ncmds;
	while (ncmds--)
	{
		if (ldcmds->cmd == cmd)
			return (ldcmds);
		ldcmds = ft_incbyte(ldcmds, ldcmds->cmdsize);
	}
	return (NULL);
}

t_btinfo	*get_btinfo(uint8_t *bin, struct symtab_command *symtab)
{
	t_btinfo *info;

	if (!(info = (t_btinfo*)malloc(sizeof(t_btinfo))))
		return (NULL);
	if (!(info->nlist = get_nlist(bin, symtab)))
		return (NULL);
	if (!(info->symtabstr = get_symtabstr(bin, symtab)))
		return (NULL);
	info->nsyms = symtab->nsyms;
	return (info);
}
