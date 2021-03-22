OBJ_DIR	:= obj/


utils = utils


OBJ_DIRS = $(addprefix $(OBJ_DIR), $(utils) )

PRE_SRCS	=	main \
				$(utils)/ft_atoi \
				$(utils)/lst_utils \
				$(utils)/malloc_free_and_exit \
				$(utils)/init_mutex_and_threads \
				$(utils)/time

OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(PRE_SRCS)))

NAME = philo_one
CC = clang
RM = rm -f

# CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror
INC = -I./includes 

all:	$(NAME)

$(NAME): $(OBJ_DIRS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME) 
	@echo "----- \e[32m $@ created\e[0m  -----"

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

$(OBJS) : includes/philo_one.h

$(CHECKER_OBJS) : includes/philo_one.h

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$@ \e[32mcreated\e[0m"


clean:	
	rm -rf $(OBJ_DIR) $(NAME)

fclean:		clean

re:		fclean all

.PHONY: all clean fclean re