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

NM_FOLDER = ./FT_NM_SRC
OTOOL_FOLDER = ./FT_OTOOL_SRC

FLAGS = -Werror -Wextra -Wall -g

all:
	@make -C $(NM_FOLDER)
	@mv $(NM_FOLDER)/$(NM) .
	@make -C $(OTOOL_FOLDER)
	@mv $(OTOOL_FOLDER)/$(OTOOL) .

clean:
	@make clean -C $(OTOOL_FOLDER)
	@make clean -C $(NM_FOLDER)

fclean: clean
	@make fclean -C $(OTOOL_FOLDER)
	@make fclean -C $(NM_FOLDER)

re: fclean all
