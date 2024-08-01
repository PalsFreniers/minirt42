##========== SOURCES ==========##

SRC = src/strings/dstring.c \
      src/strings/dstring_new.c \
      src/strings/dstring_char.c \
      src/strings/dstring_split.c \
      src/strings/dstring_trim_utils.c \
      src/strings/dstring_charp_manip.c
MAIN = src/main.c

##========== NAMES ==========##

NAME = minirt
SRCS_DIR = ./
OBJS_DIR = ./OBJ/

##========== OBJECTS ==========##

OBJS = $(addprefix $(OBJS_DIR),$(SRC:.c=.o))
MAIN_OBJ = $(addprefix $(OBJS_DIR),$(MAIN:.c=.o))

##========== COLORS ==========##

BASE_COLOR 	=		\033[0;39m
GRAY 		=		\033[0;90m
RED 		=		\033[0;91m
GREEN 		=		\033[0;92m
YELLOW 		=		\033[0;93m
BLUE 		=		\033[0;94m
MAGENTA		=		\033[0;95m
CYAN 		=		\033[0;96m
WHITE		=		\033[0;97m

##========== COMPILATOR ==========##

CC = cc

##========== LIBFT ==========##

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

##========== FLAGS ==========##

CFLAGS = -Wall -Wextra -Werror -I $(LIBFT_DIR)
LDFLAGS = $(LIBS) 
LIBS = -L $(LIBFT_DIR) -lft

##========== MODES ==========##

TIMER = 0.1

ifdef DEBUG
	CFLAGS += -g -fsanitize=thread #(address, memory, thread)
	DEBUG_MODE = 1
endif

##========== ANIMATIONS ==========##

NUM_SRC = $(words $(SRC))
INDEX = 0
NUM_LINES_TO_CLEAR = 1

all : $(CLEAR) $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(MAIN_OBJ)
	@$(CC) -o $(NAME) $(CFLAGS) $(MAIN_OBJ) $(OBJS) $(LDFLAGS)
	@echo "$(GREEN)-= $(NAME) compiled =-$(BASE_COLOR)"

$(LIBFT) :
ifdef DEBUG
	@make -C $(LIBFT_DIR) -j16 NOPRINT=1 DEBUG=1
else
	@make -C $(LIBFT_DIR) -j16 NOPRINT=1
endif
	@echo "$(GREEN)-= libft compiled =-$(BASE_COLOR)"

clean :
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS_DIR)

fclean : clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)
	@echo "$(CYAN)Files cleaned$(BASE_COLOR)"

re : fclean all

$(OBJS_DIR)%.o : %.c
	@sleep $(TIMER)
	@clear
	@echo "$(GREEN)Compiling $(NAME)$(BASE_COLOR)"
	@echo "╔==============================================╗"
	@echo -n "║$(GREEN)"
	@echo -n "▓"
	@for i in $$(seq 1 $$(expr $(INDEX) \* 45 / $(NUM_SRC))); do \
		echo -n "▓"; \
		done
	@for i in $$(seq 1 $$(expr 45 - $(INDEX) \* 45 / $(NUM_SRC))); do \
		echo -n " "; \
		done
	@echo "$(BASE_COLOR)║"
	@echo "╚==============================================╝"
	@$(eval INDEX=$(shell expr $(INDEX) + 1))
	@echo "Compiling : $<"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all bonus clean fclean re
