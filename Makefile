NAME = fdf

SRCS = fdf.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = minilibx

CC = clang
CFLAGS = -g -lmlx -framework OpenGL -framework AppKit -L $(MLX_DIR)

.PHONY : all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): %.o : %.c $(MLX_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(MLX_DIR):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
