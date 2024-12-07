NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -O2
SRCS = $(addprefix ,main.c rules.c mutexes.c philos.c error.c ft_isdigit.c ft_atoi.c ft_strlen.c ft_strncmp.c ft_putendl_fd.c)
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
