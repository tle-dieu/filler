NAME = tle-dieu.filler
CC = clang
CFLAGS = -Wall -Werror -Wextra
LDFLAG = -L./$(LIBDIR) -lft

VISUALIZER_FOLDER = visualizer/
VISUALIZER = $(VISUALIZER_FOLDER)visualizer

RESOURCES_FOLDER = resources/
MAPS_FOLDER = $(RESOURCES_FOLDER)maps/
PLAYERS_FOLDER = $(RESOURCES_FOLDER)players/
RESULT_FOLDER = result/

RM = rm -rf

SRC = main.c \
	  piece.c \
	  map.c \
	  place.c \
	  goal.c \
	  utils.c

OBJ = $(SRC:.c=.o)

LIBDIR := libft/
LIBFT := $(LIBDIR)libft.a
INCLUDE_FOLDER := $(LIBDIR)includes
INCLUDE := filler.h

GREEN := \033[38;2;12;231;58m
YELLOW := \033[38;2;251;196;15m
RED := \033[38;2;255;60;51m
RMLINE = \033[2K
NC := \033[0m

P1_EX := $(addprefix $(PLAYERS_FOLDER),$(addsuffix .filler,$(p1)))
P2_EX := $(addprefix $(PLAYERS_FOLDER),$(addsuffix .filler,$(p2)))
MAP_EX := $(addprefix $(MAPS_FOLDER),$(map))

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

all: $(NAME) $(VISUALIZER)

$(NAME): $(OBJ) $(LIBFT)
	@printf "$(RMLINE)$(YELLOW)🌘  All compiled$(NC)\n"
	@$(CC) -o $@ $(LDFLAG) $^
	@printf "$(GREEN)$(NAME) has been created$(NC)\n"
	@tput cnorm

$(LIBFT):
	@(cd $(LIBDIR) && $(MAKE))

$(VISUALIZER):
	@(cd $(VISUALIZER_FOLDER) && $(MAKE))

%.o: %.c $(INCLUDE)
	@tput civis
	@$(CC) $(CFLAGS) -I $(INCLUDE_FOLDER) -o $@ -c $<
	@printf "$(RMLINE)\r🚀 $(GREEN)$(YELLOW) Compiling:$(NC) $(notdir $<)\r"
	@sleep 0.01

clean:
	@(cd $(VISUALIZER_FOLDER) && $(MAKE) $@)
	@(cd $(LIBDIR) && $(MAKE) $@)
	@$(RM) $(OBJ)
	@printf "$(RED)The filler objects have been removed$(NC)\n"

fclean:
	@(cd $(VISUALIZER_FOLDER) && $(MAKE) $@)
	@(cd $(LIBDIR) && $(MAKE) $@)
	@$(RM) $(OBJ) $(NAME)
	@printf "$(RED)The filler objects have been removed$(NC)\n"
	@printf "$(RED)$(NAME) has been removed$(NC)\n"

run: $(NAME)
	@mkdir -p $(RESULT_FOLDER)
	@$(RM) $(RESULT_FOLDER)result.txt
	@mv $(NAME) $(PLAYERS_FOLDER)
ifneq (,$(filter $(visu),y yes))
	@(cd $(VISUALIZER_FOLDER) && $(MAKE))
	@./$(RESOURCES_FOLDER)filler_vm -f $(MAP_EX) -p1 ./$(P1_EX) -p2 ./$(P2_EX) | tee $(RESULT_FOLDER)result.txt | ./$(VISUALIZER)
else
	@./$(RESOURCES_FOLDER)filler_vm -f $(MAP_EX) -p1 ./$(P1_EX) -p2 ./$(P2_EX) | tee $(RESULT_FOLDER)result.txt
endif
	@mv filler.trace $(RESULT_FOLDER)

clean_result:
	@$(RM) $(RESULT_FOLDER)

re: fclean all

.PHONY: clean fclean run
