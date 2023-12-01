SRCS = src/ft_isalpha.c src/ft_isdigit.c src/ft_isalnum.c src/ft_isascii.c \
		src/ft_isprint.c src/ft_strlen.c src/ft_memset.c src/ft_bzero.c	\
		src/ft_memcpy.c	src/ft_memmove.c src/ft_strlcpy.c src/ft_strlcat.c \
		src/ft_toupper.c src/ft_tolower.c src/ft_strchr.c src/ft_strrchr.c \
		src/ft_strncmp.c src/ft_memchr.c src/ft_memcmp.c src/ft_strnstr.c \
		src/ft_atoi.c src/ft_calloc.c src/ft_strdup.c src/ft_substr.c \
		src/ft_strjoin.c src/ft_strtrim.c src/ft_split.c src/ft_itoa.c \
		src/ft_strmapi.c src/ft_striteri.c src/ft_putchar_fd.c src/ft_putstr_fd.c \
		src/ft_putendl_fd.c src/ft_putnbr_fd.c src/ft_lstnew_bonus.c \
		src/ft_lstadd_front_bonus.c src/ft_lstsize_bonus.c src/ft_lstlast_bonus.c \
		src/ft_lstadd_back_bonus.c src/ft_lstdelone_bonus.c src/ft_lstclear_bonus.c \
		src/ft_lstiter_bonus.c src/ft_lstmap_bonus.c

SRCSPRINTF = src/ft_printf.c src/ft_conversions.c src/ft_convhex.c \
			src/ft_convptr.c src/ft_convunsigned.c

SRCSGNL = src/get_next_line_bonus.c src/get_next_line_utils_bonus.c

OBJS = $(SRCS:.c=.o)
OBJSPRINTF = $(SRCSPRINTF:.c=.o)
OBJSGNL = $(SRCSGNL:.c=.o)

NAME = libft.a

.c.o: 
	cc -Wall -Wextra -Werror -c $< -o $(^:.c=.o) -I .

$(NAME): $(OBJS) $(OBJSPRINTF) $(OBJSGNL)
	ar rc $(NAME) $(OBJS) $(OBJSPRINTF) $(OBJSGNL)
	ranlib $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS) $(OBJSB) $(OBJSPRINTF) $(OBJSGNL)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
