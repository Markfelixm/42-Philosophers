NAME := philo
SRC := \
	philo.c \
	time.c \
	activity.c \
	print.c \
	memory.c \
	mutex.c \
	atoi.c
OBJ := $(SRC:.c=.o)
CC_FLAG := -Wall -Wextra -Werror -Ofast
DEBUG_FLAG := -fsanitize=thread -O0 -g

.PHONY: all clean fclean re debug

all: $(NAME)

$(NAME): $(OBJ)
	@echo Compiling $(NAME)...
	@cc $(CC_FLAG) $(^) -o $(@)

$(OBJ): $(SRC)
	@echo Compiling object files...
	@cc $(CC_FLAG) -c $(^)

debug: fclean
	@cc $(CC_FLAG) $(DEBUG_FLAG) -c $(SRC)
	@echo Compiling debug...
	@cc $(CC_FLAG) $(DEBUG_FLAG) $(OBJ) -o $(NAME)

clean:
	@echo Removing object files...
	@rm -f $(OBJ)

fclean: clean
	@echo Removing $(NAME)...
	@rm -f $(NAME)

re: fclean all
