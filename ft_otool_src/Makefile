OTOOL = ../ft_otool

LIBFT = ../libft
LIB = ../libft/libft.a

FLAGS = -Werror -Wextra -Wall

SRC_OTOOL = ft_otool.c \
	    dump_memory.c \
	    process_macho.c \
	    ../both/checksymtab.c \
	    ../both/error.c \
	    ../both/get_env.c \
	    ../both/get_filename.c \
	    ../both/process_fat.c \
	    ../both/process_file.c \
	    ../both/rev_bytes.c \
	    ../both/incbytes.c
	

SRCO_OTOOL = $(SRC_OTOOL:.c=.o)

all: $(OTOOL)

$(OTOOL): $(SRCO_OTOOL) $(LIB)
	gcc $(SRCO_OTOOL) $(LIB) -o $(OTOOL)

$(LIB):
	make -C $(LIBFT)

%.o: %.c
	gcc -c $(FLAGS) $< -o $@

clean:
	/bin/rm -f $(SRCO_OTOOL)
	/bin/rm -rf $(OTOOL).dSYM
	/bin/rm -f compile_commands.json
	make -C $(LIBFT) clean

fclean: clean
	/bin/rm -f $(OTOOL)
	make -C $(LIBFT) fclean

re: fclean all
