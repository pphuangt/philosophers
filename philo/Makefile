NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -O2
SRCS = $(addprefix ,main.c ft_atoi.c philos_create.c thread_process.c clear.c error.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
