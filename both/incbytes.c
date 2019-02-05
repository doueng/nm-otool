/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incbytes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 18:05:59 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 18:07:02 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	*incbytes_rev(t_env *env, void *mem, size_t inc_size)
{
	if (!mem)
		return (NULL);
	if (((void*)env->macho + env->filesize) <
						(mem + (rev_bytes(env, inc_size))))
		return (NULL);
	return (mem + (rev_bytes(env, inc_size)));
}

void	*incbytes(t_env *env, void *mem, size_t inc_size)
{
	if (!mem)
		return (NULL);
	if (((void*)env->macho + env->filesize) < (mem + inc_size))
		return (NULL);
	return (mem + inc_size);
}
