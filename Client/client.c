// Client side C program for client socket
#include "client.h"
#include <arpa/inet.h>

int main(int argc, char const* argv[]) {
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	unsigned char key[32] = {0};
	OpenKey(key);
	
	shell_start(key);
	
	/*if ((send_message(message, messageCrypt, key, sock)) < 0) {
		printf("\n Message could not be sent \n");
	}
	
	if ((receive_message(buffer, messageCrypt, key, sock)) < 0) {
		return -1;
	}*/
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	
	ClearKey(key);
	// Closing the connected socket
	return 0;
}
