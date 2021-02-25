SRCS =	main.c lst_utils.c malloc_free_and_exit.c setters.c ft_atoi.c


OBJS = ${SRCS:.c=.o}

HEADER = philo_one.h

NAME = philo_one

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

%.o: %.c	${HEADER}
			${CC} -c  $< -o ${<:.c=.o} 


$(NAME):	${OBJS}
			${CC} $(FLAGS) -o ${NAME} ${OBJS} 

all:		$(NAME)

clean:
			${RM} ${OBJS} libmlx.dylib

fclean:		clean
			${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re