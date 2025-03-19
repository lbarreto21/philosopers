CC = cc

CFLAGS =  -g -Wall -Werror -Wextra 

SRCS = philo.c set_dinner.c utils.c

NAME = philo

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

.c.o:
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME) $(OBJS)

re: fclean $(NAME)

norm:
	norminette *.c
