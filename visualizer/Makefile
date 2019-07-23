NAME = visualizer
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
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

ifneq (,$(filter $(fsanitize),y yes))
	CFLAGS += -g3
	CC = clang
ifeq ($(shell uname -s),Linux)
	CFLAGS += -fsanitize=address,undefined,integer,bounds,builtin
else
	CFLAGS += -fsanitize=address,undefined,integer,bounds
endif
endif

ifneq (,$(filter $(silent), y yes))
	HIDE :=
	SLEEP :=
	REDIRECT := > /dev/null 2>&1
endif

INCLUDE = visualizer.h
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@printf "$(RMLINE)$(YELLOW)🌘  All compiled$(NC)\n"
	@$(CC) $(CFLAGS) -o $@ $(LDFLAG) $^
	@printf "$(GREEN)$(NAME) has been created$(NC)\n"
	@tput cnorm

$(LIBFT):
	@(cd $(LIBDIR) && $(MAKE))

%.o: %.c $(INCLUDE)
	@tput civis
	@$(CC) $(CFLAGS) -I $(INCLUDE_FOLDER) -o $@ -c $<
	@printf "$(RMLINE)\r🚀 $(GREEN)$(YELLOW) Compiling:$(NC) $(notdir $<)\r"
	@sleep 0.01

clean:
	@$(RM) $(OBJ)
	@(cd $(LIBDIR) && $(MAKE) $@)
	@printf "$(RED)The visualizer objects have been removed$(NC)\n"

fclean:
	@$(RM) $(OBJ) $(NAME)
	@(cd $(LIBDIR) && $(MAKE) $@)
	@printf "$(RED)The visualizer objects have been removed$(NC)\n"
	@printf "$(RED)$(NAME) has been removed$(NC)\n"

re: fclean all

.PHONY: clean fclean
