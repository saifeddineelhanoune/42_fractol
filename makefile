NAME = fractol
SRCS = 	$(shell ls *.c)
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast -fsanitize=address
MLX = -lmlx -framework OpenGL -framework AppKit
all: $(NAME)
%.o: %.c
	$(CC) $(CFLAGS)  -Imlx -c $< -o $@
$(NAME): $(OBJS) fractol.h
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(MLX)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
