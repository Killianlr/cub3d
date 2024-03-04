
NAME = cub3d

LIBFT = libft.a

LIBFT_DIR = libft

LIB = $(addprefix $(LIBFT_DIR)/, $(LIBFT))

SRCS = main end event set_data \
		raycasting utiles_1 utiles_2 \
		parsing utiles_parsing parsing_check \
		parsing_map parsing_data_img parsing_data_color \
		affichage movement utiles_parsing_map

SOURCES = $(addsuffix .c, $(addprefix srcs/, $(SRCS))) \

OBJECTS = $(SOURCES:.c=.o)

OPENGL = -lXext -lX11 -lm
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iminilibx-linux

$(NAME): $(OBJECTS)
		make -C libft
		make -C minilibx-linux
		$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) minilibx-linux/libmlx.a $(OPENGL) $(LIB)

all: $(NAME)

clean: 
		rm -f $(OBJECTS)
		make clean -C libft

fclean: clean
		rm -f $(NAME)
		make fclean -C libft

re: clean all

mlx:
	git clone git@github.com:42Paris/minilibx-linux.git

.PHONY: all clean fclean re mlx