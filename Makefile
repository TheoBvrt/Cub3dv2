NAME = cub3D
SRCS =	./srcs/main.c \
		./srcs/rendering/render_utils.c \
		./srcs/rendering/input.c \
		./srcs/rendering/render_utils2.c \
		./srcs/rendering/movement.c \
		./srcs/rendering/rendering_textured.c \
		./srcs/parsing/parse_map.c \
		./srcs/parsing/file_checker.c \
		./srcs/parsing/parser_utils.c \
		./srcs/parsing/map_checker.c \
		./srcs/utils/utils.c \
		./srcs/utils/exit.c \

OBJS = ${SRCS:.c=.o}
CC = cc
RM = rm -f
CFLAGS = -Iheaders -Imlx -g -Wall -Wextra -Werror

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
