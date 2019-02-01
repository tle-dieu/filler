NAME = visualizer
CC = gcc
FLAG = -Wall -Werror -Wextra
LDFLAG = -L./$(LIBDIR) -lft

RM = rm -f

SRC = main.c \
	  print.c \
	  utils.c \
	  place.c \
	  parsing.c

OBJ = $(SRC:.c=.o)

LIBDIR = ../libft/
LIBFT = $(LIBDIR)libft.a
INCLUDE_FOLDER = $(LIBDIR)includes

GREEN := \033[38;2;12;231;58m
YELLOW := \033[38;2;251;196;15m
RED := \033[38;2;255;60;51m
RMLINE = \033[2K
NC := \033[0m

INCLUDE = visualizer.h
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
	@$(RM) $(OBJ)
	@printf "$(RED)The visualizer objects have been removed$(NC)\n"

fclean:
	@(cd $(LIBDIR) && $(MAKE) $@)
	@$(RM) $(OBJ) $(NAME)
	@printf "$(RED)The filler objects have been removed$(NC)\n"
	@printf "$(RED)$(NAME) has been removed$(NC)\n"

re: fclean all

.PHONY: clean fclean
