NAME := philo
SRC := \
	philo.c \
	time.c

CC_FLAG := -Wall -Wextra -Werror -g

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	@cc $(CC_FLAG) $(SRC) -o $(NAME)

clean:

fclean: clean
	@rm -f $(NAME)

re: fclean all
