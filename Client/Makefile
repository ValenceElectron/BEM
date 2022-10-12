FILES = client.h client.c ./messaging/chat_security.c ./messaging/message.c ./io/fileio.c ./inet/network.c shell.c
ARGS = -Wall -fsanitize=address
LIB = -lcrypto
EXEC = client

client:	client.c
	gcc $(FILES) $(ARGS) $(LIB) -o $(EXEC)
	
.PHONY:	test clean

test:	$(EXEC)
	./$(EXEC)
	
clean:
	rm -f $(EXEC)
