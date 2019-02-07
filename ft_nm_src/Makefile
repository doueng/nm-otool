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

LIBFT = ../libft
LIB = ../libft/libft.a

FLAGS = -Werror -Wextra -Wall

SRC_NM = $(wildcard *.c ../both/*.c)

SRCO_NM = $(SRC_NM:.c=.o)

all: $(NM)

$(NM): $(SRCO_NM) $(LIB)
	@gcc $(SRCO_NM) $(LIB) -o $(NM)

$(LIB):
	@make -C $(LIBFT)

%.o: %.c
	@gcc -c $(FLAGS) $< -o $@

clean:
	@/bin/rm -f $(SRCO_NM)
	@/bin/rm -rf $(NM).dSYM
	@/bin/rm -f compile_commands.json
	@make -C $(LIBFT) clean

fclean: clean
	@/bin/rm -f $(NM)
	@make -C $(LIBFT) fclean

re: fclean all
