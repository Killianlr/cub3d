
NAME = cub3d

SOURCES = main.c \

OBJECTS = $(SOURCES:.c=.o)

OPENGL = -lXext -lX11 -lbsd -lm
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iminilibx-linux

$(NAME): $(OBJECTS)
		make -C minilibx-linux
		$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) minilibx-linux/libmlx.a $(OPENGL)

all: $(NAME)

clean: 
		rm -f $(OBJECTS)

fclean: clean
		rm -f $(NAME)

re: clean all

mlx:
	git clone git@github.com:42Paris/minilibx-linux.git

.PHONY: all clean fclean re mlx