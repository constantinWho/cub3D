NAME	:= cub3D
CFLAGS	:= -Wextra -Wall -Werror -g3
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft

HEADERS	:= -I ./inc/ -I $(LIBMLX)/include -I $(LIBFT)/inc
LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:=  src/main.c src/ft_end_game.c \
			src/ft_init_screen.c \
			src/ft_init_viewpoint.c \
			src/ft_render_map.c \
			src/raycasting/ft_keys_listener.c \
			src/raycasting/ft_render.c \
			src/raycasting/ft_wall_to_buffer.c \
			src/raycasting/ft_render_utils.c \
			src/parser/error.c \
			src/parser/check_colors.c \
			src/parser/check_identifier.c \
			src/parser/check_walls.c \
			src/parser/check.c \
			src/parser/map.c \
			src/parser/utils.c

OBJS	:= ${SRCS:.c=.o}

all: libft libmlx $(NAME)

libft:
		make -C $(LIBFT)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -fr $(LIBMLX)/build
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
