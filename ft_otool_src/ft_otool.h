/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:25:37 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/05 19:02:56 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_OTOOL_H
# define __FT_OTOOL_H

# include "../both/nm_otool.h"

int							dump_memory(t_env *env, void *text_section);

#endif
