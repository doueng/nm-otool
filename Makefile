# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/27 16:07:21 by dengstra          #+#    #+#              #
#    Updated: 2019/01/27 16:07:23 by dengstra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NM = ft_nm
OTOOL = ft_otool

NM_FOLDER = ./ft_nm_src
OTOOL_FOLDER = ./ft_otool_src

all:
	make -C $(NM_FOLDER)
	make -C $(OTOOL_FOLDER)

clean:
	make clean -C $(OTOOL_FOLDER)
	make clean -C $(NM_FOLDER)

fclean: clean
	make fclean -C $(OTOOL_FOLDER)
	make fclean -C $(NM_FOLDER)
	/bin/rm -f $(NM)
	/bin/rm -f $(OTOOL)

re: fclean all
