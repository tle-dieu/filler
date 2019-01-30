NAME = tle-dieu.filler
CC = gcc
FLAG = -Wall -Werror -Wextra
LDFLAG = -L./$(LIBDIR) -lft

VISU_PRINTF_FOLDER = visualizer/
VISU_PRINTF = $(VISU_PRINTF_FOLDER)visu_printf

RM = rm -f

SRC = main.c \
	  piece.c \
	  map.c \
	  place.c \
	  goal.c \
	  utils.c

OBJ = $(SRC:.c=.o)

LIBDIR = libft/
LIBFT = $(LIBDIR)libft.a
INCLUDE_FOLDER = $(LIBDIR)includes

GREEN := \033[38;2;12;231;58m
YELLOW := \033[38;2;251;196;15m
RED := \033[38;2;255;60;51m
RMLINE = \033[2K
NC := \033[0m

declare map = 1;
declare p1 = 2;
declare p2 = 3;

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@printf "$(RMLINE)$(YELLOW)All compiled$(NC)\n"
	@$(CC) -o $@ $(LDFLAG) $^
	@printf "$(GREEN)$(NAME) has been created$(NC)\n"
	@tput cnorm

$(LIBFT):
	@(cd $(LIBDIR) && $(MAKE))

%.o: %.c $(INCLUDE)
	@tput civis
	@$(CC) $(FLAG) -I $(INCLUDE_FOLDER) -o $@ -c $<
	@printf "$(RMLINE)\r🚀 $(GREEN)$(YELLOW) Compiling:$(NC) $(notdir $<)\r"
	@sleep 0.01

clean:
	@(cd $(LIBDIR) && $(MAKE) $@)
	@$(RM) $(OBJ)
	@printf "$(RED)The filler objects have been removed$(NC)\n"

fclean:
	@(cd $(LIBDIR) && $(MAKE) $@)
	@$(RM) $(OBJ) $(NAME)
	@printf "$(RED)The filler objects have been removed$(NC)\n"
	@printf "$(RED)$(NAME) has been removed$(NC)\n"

test: $(NAME)
	@-mkdir -p result
	@-rm -f result/result.txt
	@-rm -f result/read.txt
	@-mv tle-dieu.filler resources/players
	@-././resources/filler_vm -f resources/maps/$(map) -p1 resources/players/./$(p1).filler -p2 resources/players/./$(p2).filler | tee result/result.txt
	@-mv filler.trace result

visu:
	(cd visualizer && gcc -I /usr/local/include visualizer.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -L ../libft/ -lft)
	resources/./filler_vm -f resources/maps/map00 -p1 ./tle-dieu.filler -p2 resources/players/superjeannot.filler | visualizer/./a.out
	
visu_printf: $(NAME) $(VISU_PRINTF)
	make -C visualizer
	@-mkdir -p result
	@-rm -f result/result.txt
	@-rm -f result/read.txt
	@-mv tle-dieu.filler resources/players
	@-././resources/filler_vm -f resources/maps/$(map) -p1 resources/players/./$(p1).filler -p2 resources/players/./$(p2).filler | tee test.txt | visualizer/./visu_printf
	@-mv filler.trace result

$(VISU_PRINTF):
	@(cd $(VISU_PRINTF_FOLDER) && $(MAKE))

re: fclean all

.PHONY: clean fclean
