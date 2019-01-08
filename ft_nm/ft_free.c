#include "ft_nm.h"


void	free_btinfo(t_btinfo *btinfo)
{
	free(btinfo->nlist);
	free(btinfo->symtabstr);
	free(btinfo);
}

void	free_nmtree(t_nmtree *symbol)
{
	if (!symbol)
		return ;
	if (symbol->left)
		free_nmtree(symbol->left);
	if (symbol->right)
		free_nmtree(symbol->right);
	free(symbol);
}
