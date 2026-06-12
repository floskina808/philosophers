CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
HEADER = philosophers.h
TARGET = philo

SRC = main.c utils.c init.c fork.c philo.c philo_cycle.c philo_forks.c monitor.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
