NAME = tle-dieu.filler
CC = gcc
FLAG = -Wall -Werror -Wextra
LDFLAG = -L./$(LIBDIR) -lft

VISU_FOLDER = visualizer/
VISU = $(VISU_FOLDER)visualizer

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
INCLUDE = filler.h

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
	@printf "$(RMLINE)$(YELLOW)🌘  All compiled$(NC)\n"
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
	@(cd $(VISU_FOLDER) && $(MAKE) $@)
	@$(RM) $(OBJ)
	@printf "$(RED)The filler objects have been removed$(NC)\n"

fclean:
	@(cd $(LIBDIR) && $(MAKE) $@)
	@(cd $(VISU_FOLDER) && $(MAKE) $@)
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

visu: $(NAME)
	make -C $(VISU_FOLDER)
	@-mkdir -p result
	@-rm -f result/result.txt
	@-rm -f result/read.txt
	@-mv tle-dieu.filler resources/players
	@-././resources/filler_vm -f resources/maps/$(map) -p1 resources/players/./$(p1).filler -p2 resources/players/./$(p2).filler | tee result/result.txt | ./$(VISU)
	@-mv filler.trace result

$(VISU):
	@(cd $(VISU_FOLDER) && $(MAKE))

re: fclean all

.PHONY: clean fclean visu
