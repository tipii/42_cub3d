NAME = cub3D
SOURCES_DIR = ./sources
OBJECTS_DIR = ./obj
INCLUDES_DIR = ./includes

G3 =  -g3 -fsanitize=address
COMPIL = gcc
FLAG = -Wall -Wextra -Werror
HEADER = -I $(INCLUDES_DIR)
LIB = -lmlx -framework OpenGL -framework AppKit

SRCS_NAME = bmp.c draw.c error.c ft_split.c get_next_line_utils.c get_next_line.c hud.c init_env.c \
		init.c keyboard.c load_textures_utils.c load_textures.c main.c parse_found_text.c parse_found.c \
		parse_map.c parse_utils_suite.c parse_utils.c parse.c player_move.c player_position.c \
		player.c raycast_floor.c raycast_wall.c raycast.c sprites.c

SRCS = $(addprefix $(SOURCES_DIR)/,$(SRCS_NAME))
OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(COMPIL) $(FLAG) $(LIB) $(HEADER) $(OBJS) -o $(NAME)

%.o: %.c
			$(COMPIL) $(FLAG) $(HEADER) -c $< -o $@
			
all:		$(NAME)

bonus:		$(NAME)
			
clean :
			rm -f $(OBJS)

fclean :	clean
			rm -f ./$(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re
