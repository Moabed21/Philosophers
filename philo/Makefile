NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c utils.c init.c routine.c utils2.c
OBJ =$(SRC:.c=.o)
RM = rm -f
all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean : $(NAME)
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re:fclean all
