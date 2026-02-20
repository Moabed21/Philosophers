NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/init.c \
       $(SRC_DIR)/init2.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/utils2.c \
       $(SRC_DIR)/utils3.c \
       $(SRC_DIR)/routine.c 

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
RM = rm -f
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c src/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)/*.o

fclean: clean
	$(RM) $(NAME)

re: fclean all