NAME	:= cub3D
CFLAGS	:= -Wextra -Wall -Werror -g3 -fsanitize=address
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft

HEADERS	:= -I ./inc/ -I $(LIBMLX)/include -I $(LIBFT)/inc
LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= src/main.c src/render.c src/raycaster.c src/keys.c src/check.c src/error.c src/check_walls.c src/check_colors.c src/map.c src/check_identifier.c\

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
