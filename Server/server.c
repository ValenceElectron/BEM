// Server side software for my calorie counting application.
#include "server.h"
#include <netinet/in.h>
#include <stdlib.h>
#include <math.h>
#define PORT 12001

int main(int argc, char const* argv[]) {
	int server_fd, new_socket;
	struct sockaddr_in address;
	unsigned char message[MSGSIZE] = "This is an encrypted message from the server";
	unsigned char messageCrypt[MSGSIZE] = { 0 };
	unsigned char buffer[MSGSIZE + 1] = {0};
	// char* hello = "Hello from server\n";
	
	int opt = 1;
	int addrlen = sizeof(address);
	
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation failed\n");
		return -1;
	}

	//Forcefully attaching socket to port 12001
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
			&opt, sizeof(opt))) {
		printf("\n Couldn't attach socket to port \n");
		return -1;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	//Forcefully attaching socket to the port 12001
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		printf("\n Bind failed \n");
		return -1;
	}
	if (listen(server_fd, 3) < 0) {
		printf("\n Socket couldn't listen \n");
		return -1;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	while (1) { // main server loop
		if ((new_socket
			= accept(server_fd, (struct sockaddr*) &address,
			(socklen_t*) &addrlen)) < 0) {
			printf("\n Couldn't create connection socket  \n");
			return -1;
		}

		unsigned char key[32] = {0};
		OpenKey(key);
		
		if ((receive_message(buffer, messageCrypt, key, new_socket)) < 0) {
			printf("\n Failed to read any incoming messages \n");
		}
		
		if ((send_message(message, messageCrypt, key, new_socket)) < 0) {
			printf("\n Message could not be sent \n");
		}
		
		ClearKey(key);
		close(new_socket);
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}
