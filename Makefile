NAME = cube3d
SOURCES_DIR = ./sources/
INCLUDES_DIR = ./includes

COMPIL = gcc
FLAG = -Wall -Wextra -Werror

HEADER = -I $(INCLUDES_DIR)

SRCS = $(wildcard $(SOURCES_DIR)*.c)
OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(COMPIL) $(FLAG) $(HEADER) $(OBJS) -o $(NAME).o 
			./$(NAME).o

%.o: %.c
			$(COMPIL) $(FLAG) $(HEADER) -c $< -o $@
			
all:		$(NAME)
			
clean :
			rm -f $(OBJS)

fclean :	clean
			rm -f ./$(NAME).o

re:			fclean all

.PHONY:		all bonus clean fclean re
