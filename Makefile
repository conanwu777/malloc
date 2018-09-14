ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc.so
NAME1 = malloc
NAME2 = demo
LNKNAME = libft_malloc_$(HOSTTYPE).so
CC = @gcc
CFLAGS = -Wall -Wextra -Werror
SRC = malloc.c support.c output.c realloc.c
SRC1 = main.c
SRC2 = demo.c malloc.c support.c output.c realloc.c
DEP = malloc.h
OBJ = $(SRC:.c=.o)
OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)
FT_LNK = -L ./libft -lft
ML_LNK = -L. -lft_malloc

RED = "\033[1;38;2;225;20;20m"
ORANGE = "\033[1;38;2;255;120;10m"
YELLO = "\033[1;38;2;255;200;0m"
GREEN = "\033[1;38;2;0;170;101m"
LG = "\033[1;38;2;167;244;66m"
BLUE = "\033[1;38;2;50;150;250m"
PURPLE = "\033[1;38;2;150;75;255m"
WHITE = "\033[1;38;2;255;250;232m"

all: $(NAME)

libft/%:
	@echo $(YELLO)
	@make -C libft

$(NAME) : $(LNKNAME)
	@echo $(ORANGE)Building symbolic link
	@ln -fs $(LNKNAME) $(NAME)
	@echo $(LG)Making $(NAME1)
	$(CC) $(CFLAGS) $(FT_LNK) $(ML_LNK) $(SRC1) -o $(NAME1)
	@echo $(LG)Making $(NAME2)
	$(CC) $(CFLAGS) $(FT_LNK) $(SRC2) -o $(NAME2)

$(LNKNAME): $(OBJ) $(OBJ1) $(OBJ2) $(DEP) libft/libft.a
	@echo $(ORANGE)Making $(LNKNAME)
	@$(CC) -shared $(FT_LNK) -o $@ $(OBJ)

%.o: %.c $(DEP) libft/libft.a
	@echo $(YELLO)Making $@
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@make clean -C libft
	@echo $(RED)Cleaning o files
	@rm -f $(OBJ)
	@rm -f $(OBJ1)
	@rm -f $(OBJ2)

fclean: clean
	@make fclean -C libft
	@echo $(RED)Removing excutables
	@rm -f $(LNKNAME)
	@rm -f $(NAME)
	@rm -f $(NAME1)
	@rm -f $(NAME2)

re:	fclean all
