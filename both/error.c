#include "nm_otool.h"

void	*ft_error(char *error_text)
{
	ft_printf("%s\n", error_text);
	return (NULL);
}

int		ft_error_one(char *error_text)
{
	ft_printf("%s\n", error_text);
	return (-1);
}
