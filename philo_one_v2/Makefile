SRCS =	main.c ft_atoi.c malloc_free_and_exit.c lst_utils.c time.c

OBJS = ${SRCS:.c=.o}

HEADER = philo_one.h

NAME = philo_one

CC = gcc

RM = rm -f

LIB=-lpthread

FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

%.o: %.c	${HEADER}
			${CC} ${FLAGS} -c  $< -o ${<:.c=.o} 


$(NAME):	${OBJS}
			${CC} $(FLAGS) ${OBJS} ${LIB} -o ${NAME}  

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re

