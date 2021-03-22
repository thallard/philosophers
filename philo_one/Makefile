OBJ_DIR	:= obj/


utils = utils
main = main

OBJ_DIRS = $(addprefix $(OBJ_DIR), $(utils) $(main))

PRE_SRCS	=	main \
				$(utils)/ft_atoi \
				$(utils)/lst_utils \
				$(utils)/malloc_free_and_exit \
				$(utils)/init_mutex_and_threads \
				$(utils)/time \
				$(utils)/parsing_and_setters \
				$(main)/actions 

OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(PRE_SRCS)))

NAME = philo_one
CC = clang
RM = rm -f

# CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread
CFLAGS = -Wall -Wextra -Werror
INC = -I./includes 

all:	$(NAME)

$(NAME): $(OBJ_DIRS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME) 
	@echo "----- \033[32m$@ created\033[0m  -----"

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

$(OBJS) : includes/philo_one.h

$(CHECKER_OBJS) : includes/philo_one.h

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$@ \033[32mcreated\033[0m"


clean:	
	rm -rf $(OBJ_DIR) $(NAME)

fclean:		clean

re:		fclean all

.PHONY: all clean fclean re