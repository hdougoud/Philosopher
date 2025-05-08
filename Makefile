NAME	= philo
CC 		= gcc
FLAGS	= -Wall -Wextra -Werror -g

SRCS	= main.c ft_atoi.c utils.c init.c threads.c activity_utils.c activity.c monitoring.c
SRC_DIR = Sources/
SOURCES = $(addprefix $(SRC_DIR), $(SRCS))

OBJ_DIR = Objects/
OBJS	= $(notdir $(SOURCES:.c=.o))
OBJECTS = $(addprefix $(OBJ_DIR), $(OBJS))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJECTS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean

re: fclean all

bonus:
	$(MAKE) -C philo_bonus

.PHONY: all clean fclean re

