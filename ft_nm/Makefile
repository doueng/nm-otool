NM = ft_nm

LIBFT = ../libft
LIB = ../libft/libft.a

#FLAGS =
FLAGS = -Werror -Wextra -Wall -g

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
