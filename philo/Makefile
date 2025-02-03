MAKEFLAGS += --silent

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRCS = main.c errors.c utils.c init.c check.c routine.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compiled $(NAME) successfully!"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@echo "Make correctely clean"

fclean: clean
	rm -f $(NAME)
	@echo "Suppresed $(NAME) successfully"

re: fclean all

.PHONY: all clean fclean re


