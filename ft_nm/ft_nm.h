/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:05:15 by dengstra          #+#    #+#             */
/*   Updated: 2019/01/27 18:20:46 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_NM_H
# define __FT_NM_H

# include "../both/nm_otool.h"

typedef struct				s_nmtree
{
	char					*name;
	/* struct section_64		*sections; */
	struct nlist_64			*nlist;
	struct s_nmtree			*left;
	struct s_nmtree			*right;
}							t_nmtree;

typedef struct				s_btinfo
{
	uint32_t				nsyms;
	struct nlist_64			*nlist;
	char					*symtabstr;
	struct section_64		*sections;
}							t_btinfo;

# define					NUM_OP 0b1
# define					REV_OP 0b10
# define					P_OP 0b100

int							process_file(char *filename, int options);
int							process_macho(uint8_t *bin, int options);
struct load_command			*get_ldcmd(t_env *env, uint32_t cmd);
t_btinfo					*get_btinfo(uint8_t *bin,
											struct symtab_command *symtab);
void						free_env(t_env *env);
void						free_btinfo(t_btinfo *btinfo);
void						free_nmtree(t_nmtree *root);
t_nmtree					*insert_symbols(t_btinfo *btinfo, int options);
void						print_tree(t_nmtree *symbol,
											void (*print_function)(t_nmtree *));
void						print_standard(t_nmtree *symbol);
int							alpha_order_compare(t_nmtree *new,
											t_nmtree *to_compare, int options);
int							num_order_compare(t_nmtree *new,
											t_nmtree *to_compare, int options);
int							symbol_order_compare(t_nmtree *new,
											t_nmtree *to_compare, int options);
#endif
