NAME	= philo
BNS_NM	= philo_bonus
CC 		= gcc
FLAGS	= -Wall -Wextra -Werror -g

SRCS	= main.c ft_atoi.c print_error.c utils.c memory_utils.c timer.c init.c threads.c free_all.c \
			activity.c activity_utils.c
SRC_DIR = Sources/
SOURCES = $(addprefix $(SRC_DIR), $(SRCS))

BNS		= philo_bonus.c
BNS_DIR = philo_bonus/src/
BONUS	= $(addprefix $(BNS_DIR), $(BNS))

OBJ_DIR = Objects/
OBJS	= $(notdir $(SOURCES:.c=.o))
OBJ_BNS = $(notdir $(BONUS:.c=.o))
OBJECTS = $(addprefix $(OBJ_DIR), $(OBJS))
BONUS_OBJECT = $(addprefix $(OBJ_DIR), $(OBJ_BNS))

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
	$(OBJ_DIR), $(BNS_NM)

.PHONY: all clean fclean re

