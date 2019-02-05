/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:25:37 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 18:27:07 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_OTOOL_H_
# define __FT_OTOOL_H_

# include "../both/nm_otool.h"

int							dump_memory(t_env *env, void *text_section);
int							process_file(char *filename, int options);
int							process_macho(t_env *env, int options);

#endif
