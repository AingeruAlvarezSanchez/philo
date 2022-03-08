SHELL = /bin/sh
NAME = philo
FILES = philo		\
	initials	\
	utils		\
	actions

CC = cc
FLAGS = -Wall -Werror -Wextra -pthread #-fsanitize=address -g3
RM = rm -rf

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "EXECUTABLE CREATED"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "OBJECT CREATED"

clean:
	@$(RM) $(OBJS)
	@echo "OBJECTS PURGED"

fclean: clean
	@$(RM) $(NAME)
	@echo "EXECUTABLE PURGED"

re: clean all

.PHONY: all clean fclean re
