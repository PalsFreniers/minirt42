##========== SOURCES ==========##

SRC =  src/files/fmap.c
SRC += src/scene/free.c \
       src/scene/print.c \
       src/scene/append.c 
SRC += src/logger/logger.c \
       src/logger/logger_v.c \
       src/logger/logger_impl.c
SRC += src/object/print.c \
       src/object/object.c \
       src/object/print_light.c \
       src/object/print_plane.c \
       src/object/print_sphere.c \
       src/object/print_cylinder.c
SRC += src/parsing/obey.c \
       src/parsing/parse_file.c \
       src/parsing/parse_line.c \
       src/parsing/parse_color.c \
       src/parsing/parse_range.c \
       src/parsing/parse_light.c \
       src/parsing/parse_float.c \
       src/parsing/parse_plane.c \
       src/parsing/parse_sphere.c \
       src/parsing/parse_camera.c \
       src/parsing/parse_cylinder.c \
       src/parsing/parse_position.c \
       src/parsing/parse_ranged_vector.c \
       src/parsing/parse_ambient_light.c
SRC += src/strings/dstring.c \
       src/strings/dstring_new.c \
       src/strings/dstring_char.c \
       src/strings/dstring_conv1.c \
       src/strings/dstring_conv2.c \
       src/strings/dstring_conv3.c \
       src/strings/dstring_conv4.c \
       src/strings/dstring_conv5.c \
       src/strings/dstring_conv6.c \
       src/strings/dstring_conv7.c \
       src/strings/dstring_split.c \
       src/strings/dstring_equals.c \
       src/strings/dstring_trim_utils.c \
       src/strings/dstring_charp_manip.c
SRC += src/ui/vline.c \
       src/ui/button.c \
       src/ui/numpad.c \
       src/ui/button2.c
SRC += src/mlx/mmlx.c \
       src/mlx/hooks.c
SRC += src/actions/buttons_actions.c \
       src/actions/button_actions_2.c \
       src/actions/buttons_actions_3.c \
       src/actions/buttons_actions_4.c \
       src/actions/buttons_actions_modify_plane.c \
       src/actions/buttons_actions_modify_light.c \
       src/actions/buttons_actions_modify_sphere.c \
       src/actions/buttons_actions_mod_obj_color.c \
       src/actions/buttons_actions_mod_obj_float.c \
       src/actions/buttons_actions_modify_ambient.c \
       src/actions/buttons_actions_mod_obj_vector3.c \
       src/actions/buttons_actions_mod_obj_float_2.c \
       src/actions/buttons_actions_modify_cylinder.c
SRC += src/save/save_vec3.c \
       src/save/save_float.c \
       src/save/save_color.c \
       src/save/save_light.c \
       src/save/save_plane.c \
       src/save/save_sphere.c \
       src/save/save_camera.c \
       src/save/save_cylinder.c \
       src/save/save_ambient_light.c
SRC += src/math/la.c
SRC += src/render/loop_render.c
SRC += src/render/collision/sphere.c
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

CC = clang

##========== LIBFT ==========##

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

##========== MLX ==========##

MLX_DIR = ./mlx
MLX = $(MLX_DIR)/libmlx.so

##========== FLAGS ==========##

CFLAGS = -Wall -Wextra -Werror -I $(LIBFT_DIR) -I ./src/ -I $(MLX_DIR)/includes
LDFLAGS = -Wl,-rpath=$(MLX_DIR) $(LIBS) 
LIBS = -lm -L $(LIBFT_DIR) -lft -L $(MLX_DIR) -lmlx -lSDL2

##========== MODES ==========##

TIMER = 0.1

ifdef DEBUG
	CFLAGS += -g -gdwarf-2 #-fsanitize=address #(address, memory, thread)
	DEBUG_MODE = 1
endif

##========== ANIMATIONS ==========##

NUM_SRC = $(words $(SRC))
INDEX = 0
NUM_LINES_TO_CLEAR = 1

all : $(CLEAR) $(NAME)

$(NAME) : $(MLX) $(OBJS) $(LIBFT) $(MAIN_OBJ)
	@echo -n " + "
	$(CC) -o $(NAME) $(CFLAGS) $(MAIN_OBJ) $(OBJS) $(LDFLAGS)
	@echo "$(GREEN)-= $(NAME) compiled =-$(BASE_COLOR)"

$(LIBFT) :
ifdef DEBUG
	@make -C $(LIBFT_DIR) -j16 NOPRINT=1 DEBUG=1
else
	@make -C $(LIBFT_DIR) -j16 NOPRINT=1
endif
	@echo "$(GREEN)-= libft compiled =-$(BASE_COLOR)"

$(MLX_DIR):
	@git clone https://github.com/seekrs/MacroLibX.git $(MLX_DIR)

$(MLX) : $(MLX_DIR)
	@make -C $(MLX_DIR) -j16
	@echo "$(GREEN)-= mlx compiled =-$(BASE_COLOR)"

clean :
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(MLX_DIR)
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
	@echo "╔══════════════════════════════════════════════╗"
	@echo -n "║$(GREEN)"
	@echo -n "▓"
	@for i in $$(seq 1 $$(expr $(INDEX) \* 45 / $(NUM_SRC))); do \
		echo -n "▓"; \
		done
	@for i in $$(seq 1 $$(expr 45 - $(INDEX) \* 45 / $(NUM_SRC))); do \
		echo -n " "; \
		done
	@echo "$(BASE_COLOR)║"
	@echo "╚══════════════════════════════════════════════╝"
	@$(eval INDEX=$(shell expr $(INDEX) + 1))
	@echo "Compiling : $<"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all bonus clean fclean re
