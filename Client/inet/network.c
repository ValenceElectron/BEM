#include "../client.h"
#include <arpa/inet.h>
#define PORT 12001

int network_initialize(int *client_fd) {
	int sock = 0;
	struct sockaddr_in serv_addr;
	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 address from text to binary
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("\n Invalid address/Address not supported \n");
		return -1;
	}
	
	if ((*client_fd = connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))) < 0) {
		printf("\n Connection Failed \n");
		return -1;
	}
	
	return sock;
}

void network_shutdown(int *client_fd) {
	int client = *client_fd;
	close(client);
}
