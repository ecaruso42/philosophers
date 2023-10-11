NAME = philo

SRCS = \
		main.c

FLAGS = -Wall -Werror -Wextra
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