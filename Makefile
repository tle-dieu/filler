NAME = tle-dieu.filler
CC = gcc
FLAG = -Wall -Werror -Wextra
LDFLAG = -L./$(LIBDIR) -lft

RM = rm -f

SRC = main.c

OBJ = $(SRC:.c=.o)

LIBDIR = libft/
LIBFT = $(LIBDIR)libft.a
INCLUDE_FOLDER = $(LIBDIR)includes

GREEN := \033[38;2;12;231;58m
YELLOW := \033[38;2;251;196;15m
RED := \033[38;2;255;60;51m
RMLINE = \033[2K
NC := \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) -o $@ $(LDFLAG) $^
	@printf "$(GREEN)$(NAME) has been created$(NC)\n"

$(LIBFT):
	@(cd $(LIBDIR) && $(MAKE))

%.o: %.c $(INCLUDE)
	@$(CC) $(FLAG) -I $(INCLUDE_FOLDER) -o $@ -c $<
	@printf "$(RMLINE)\r🚀 $(GREEN)$(YELLOW) Compiling:$(NC) $(notdir $<)\r"
	@sleep 0.05

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
	@-././resources/filler_vm -f resources/maps/map01 -p1 resources/players/abanlin.filler -p2 ./tle-dieu.filler | tee result/result.txt
	@-mv filler.trace result
	@printf "\n$(YELLOW)###############FT_DPRINTF###############\n$(NC)\n"
	@cat result/read.txt
	@printf "$(YELLOW)#################RESULT#################\n$(NC)\n"
	@tail -n 71 result/result.txt

re: fclean all

.PHONY: clean fclean
