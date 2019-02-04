OTOOL = ft_otool

LIBFT = ../libft
LIB = ../libft/libft.a

#FLAGS =
FLAGS = -Werror -Wextra -Wall -g

SRC_OTOOL = $(wildcard *.c ../both/*.c)

SRCO_OTOOL = $(SRC_OTOOL:.c=.o)

all: $(OTOOL)

$(OTOOL): $(SRCO_OTOOL) $(LIB)
	@gcc $(SRCO_OTOOL) $(LIB) -o $(OTOOL)

$(LIB):
	@make -C $(LIBFT)

%.o: %.c
	@gcc -c $(FLAGS) $< -o $@

clean:
	@/bin/rm -f $(SRCO_OTOOL)
	@/bin/rm -rf $(OTOOL).dSYM
	@/bin/rm -f compile_commands.json
	@make -C $(LIBFT) clean

fclean:
	@/bin/rm -f $(OTOOL)
	@make -C $(LIBFT) fclean

re: fclean all
