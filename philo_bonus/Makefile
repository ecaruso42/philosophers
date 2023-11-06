NAME = philo

SRCS = \
		main.c \
		philo_init.c \
		philo_routine.c

FLAGS = -Wall -Werror -Wextra -g -pthread
CC = gcc $(FLAGS)
RM = rm -f

OBJS = $(SRCS:%.c=%.o)

$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME)

all : $(NAME)

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re