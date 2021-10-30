NAME = fdf

SRCS = fdf.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = minilibx/

CC = clang
CFLAGS = -g
LFLAGS = $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -L $(MLX_DIR)

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
    LFLAGS = $(CFLAGS) -lmlx -lXext -lX11 -lm -L $(MLX_DIR)
endif

.PHONY : all clean fclean re

all: $(NAME)

$(NAME): mlx $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

$(OBJS): %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

mlx:
	@echo "=========== Compiling MinilibX ==========="
	$(MAKE) -C $(MLX_DIR)
	@echo "========= End Compiling MinilibX ========="

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
