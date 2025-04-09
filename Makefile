CC = cc

CFLAGS =  -g -Wall -Werror -Wextra 

SRCS = philo.c \
set_dinner.c \
utils.c \
verifications.c \
utils2.c \
philos_routine.c \
monitoring.c

NAME = philo

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME) $(OBJS)

re: fclean $(NAME)

norm:
	norminette *.c
