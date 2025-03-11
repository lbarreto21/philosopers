CC = cc

CFLAGS =  -g -Wall -Werror -Wextra 

SRCS = 

NAME = philo

LIB = libft/libft.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB)

.c.o:
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME) $(OBJS)

re: fclean $(NAME)

norm:
	norminette *.c
