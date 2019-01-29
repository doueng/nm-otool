/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:04:52 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/28 18:59:32 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_env		*get_env(uint8_t *bin)
{
	t_env					*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	env->macho = (struct mach_header_64*)bin;
	bin += sizeof(struct mach_header_64);
	env->ldcmds = (struct load_command*)bin;
	// if (!(env->sections = get_allsects(bin, env->ldcmds, env->macho->ncmds)))
		// return (NULL);
	/* ft_printf("sizeofldcmds %d\n", env->macho->sizeofcmds); */
	env->sections = (struct section_64*)(bin + env->macho->sizeofcmds + (env->macho->sizeofcmds % 8)); // change to 4 for 32 bit
	// ft_printf("%llu\n", *((uint64_t*)(bin + env->macho->sizeofcmds)));
	/* ft_printf("header size %x\n", sizeof(struct mach_header_64)); */
	// ft_printf("offset %llx\n", sizeof(struct mach_header_64) + env->macho->sizeofcmds + (env->macho->sizeofcmds % 8));
	/* ft_printf("offset %llx\n", env->macho->sizeofcmds + (env->macho->sizeofcmds % 8)); */
	return (env);
}
