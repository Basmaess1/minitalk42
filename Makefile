CFLAGS = -Wall -Wextra -Werror
CC = cc
SRCS = ft_printf.c
SERVER = server
CLIENT = client
SERVERB = server_bonus
CLIENTB = client_bonus
OBJS = $(SRCS:.c=.o)

all : $(SERVER) $(CLIENT)

bonus : $(SERVERB) $(CLIENTB)

$(SERVER) : server.c $(OBJS)
			$(CC) $(CFLAGS) server.c $(OBJS) -o $(SERVER)

$(CLIENT) : client.c $(OBJS)
			$(CC) $(CFLAGS) client.c $(OBJS) -o $(CLIENT)

$(SERVERB) : server_bonus.c $(OBJS)
			$(CC) $(CFLAGS) server_bonus.c $(OBJS) -o $(SERVERB)

$(CLIENTB) : client_bonus.c $(OBJS)
			$(CC) $(CFLAGS) client_bonus.c $(OBJS) -o $(CLIENTB)
		
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVERB) $(CLIENTB)

re: fclean all

.PHONY: all clean fclean re