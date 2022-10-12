FILES = server.h server.c ./messaging/chat_security.c ./messaging/message.c ./io/fileio.c
ARGS = -Wall -fsanitize=address
LIB = -lcrypto
EXEC = server

client: server.c
	gcc $(FILES) $(ARGS) $(LIB) -o $(EXEC)
	
.PHONY: test clean

test: $(EXEC)
	./$(EXEC)
	
clean:
	rm -f $(EXEC)
