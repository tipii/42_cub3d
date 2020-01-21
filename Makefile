NAME = cub3D
SOURCES_DIR = ./sources/
INCLUDES_DIR = ./includes

COMPIL = gcc
FLAG = -Wall -Wextra -Werror
G3 =  -g3 -fsanitize=address
HEADER = -I $(INCLUDES_DIR)
LIB = -lmlx -framework OpenGL -framework AppKit
SRCS = $(wildcard $(SOURCES_DIR)*.c)
OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(COMPIL) $(FLAG) $(G3) $(LIB) $(HEADER) $(OBJS) -o $(NAME)
			# ./$(NAME)

%.o: %.c
			$(COMPIL) $(FLAG) $(HEADER) -c $< -o $@
			
all:		$(NAME)
			
clean :
			rm -f $(OBJS)

fclean :	clean
			rm -f ./$(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re
