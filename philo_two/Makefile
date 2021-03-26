OBJ_DIR	:= obj/

srcs = srcs
main = main

OBJ_DIRS = $(addprefix $(OBJ_DIR), $(srcs) $(main))

PRE_SRCS	=	main \
				$(srcs)/ft_atoi \
				$(srcs)/lst_utils \
				$(srcs)/malloc_free_and_exit \
				$(srcs)/init_mutex_and_threads \
				$(srcs)/time \
				$(srcs)/parsing_and_setters \
				$(srcs)/actions 

OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(PRE_SRCS)))

NAME = philo_two
CC = clang
RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g3 
INC = -I./includes 

all:	$(NAME)

$(NAME): $(OBJ_DIRS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME) 
	@echo "----- \033[32m$@ created\033[0m  -----"

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

$(OBJS) : includes/philo_two.h

$(CHECKER_OBJS) : includes/philo_two.h

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$@ \033[32mcreated\033[0m"

clean:	
	rm -rf $(OBJ_DIR) $(NAME)

fclean:		clean

re:		fclean all

.PHONY: all clean fclean re