NAME = philo
INCLUDES = includes
CC = cc
CFLAGS = -Wall -Wextra -Werror -O2
HEADERS = -I./$(INCLUDES)
SRCS = $(addprefix srcs/, main.c time.c print.c\
	   $(addprefix init/, rules.c mutexes.c philos.c threads.c set_time.c) \
	   $(addprefix philosopher/, philosopher.c forks.c state.c usleep.c) \
	   $(addprefix monitor/, monitor.c broadcast.c) \
	   $(addprefix utils/, ft_isdigit.c ft_atoi.c ft_strlen.c ft_strncmp.c\
	   ft_putendl_fd.c err_ret.c))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(HEADERS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $(HEADERS) -o $@ $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
