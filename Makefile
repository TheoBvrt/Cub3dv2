NAME = cub3d
SRCS =	./srcs/main.c \
		./srcs/rendering/render_utils.c \
		./srcs/rendering/input.c \
		./srcs/rendering/rendering.c \
		./srcs/rendering/movement.c \
		./srcs/parsing/parse_map.c \
		./srcs/parsing/error_checker.c \
		./srcs/parsing/parser_utils.c

OBJS = ${SRCS:.c=.o}
CC = gcc
RM = rm -f
CFLAGS = -Iheaders -Imlx -g

all : ${NAME}

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${OBJS}
	${MAKE} -C ./libft 
	$(CC) $(OBJS) ./libft/libft.a -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

clean:
	${RM} ${OBJS} 
	make clean -C ./libft

fclean: clean
	${RM} ${NAME}
	make fclean -C ./libft

re: fclean all