NAME = fdf

SRCS = fdf.c
SRCS_DIR = src

OBJS = $(SRCS:.c=.o)
OBJS_DIR = obj

_SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS))
_OBJS = $(addprefix $(OBJS_DIR)/, $(OBJS))

HEADERS = includes
MLX_DIR = minilibx

CC = clang
CFLAGS = -g -I $(HEADERS)
LFLAGS = $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -L $(MLX_DIR)

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
    LFLAGS = $(CFLAGS) -lmlx -lXext -lX11 -lm -L $(MLX_DIR)
endif

.PHONY : all mlx mlx_clean clean fclean re

all: $(NAME)

$(NAME): $(_OBJS)
	$(CC) $(_OBJS) $(LFLAGS) -o $(NAME)

$(_OBJS): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c $(OBJS_DIR) mlx
	$(CC) -c $(CFLAGS) $< -o $@

mlx:
	@echo "=========== Compiling MinilibX ==========="
	$(MAKE) -C $(MLX_DIR)
	cp $(MLX_DIR)/mlx.h $(HEADERS)/mlx.h
	@echo "========= End Compiling MinilibX ========="

mlx_clean:
	@echo "=========== Compiling MinilibX ==========="
	$(MAKE) -C $(MLX_DIR) clean
	rm $(HEADERS)/mlx.h
	@echo "========= End Compiling MinilibX ========="

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
