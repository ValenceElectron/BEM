#include "../client.h"


int send_message(void *msg, void *cptmsg, void *key, int sock) {
	chat_encrypt(key, msg, MSGSIZE - 16, cptmsg);
	return send(sock, cptmsg, MSGSIZE, 0);
}

int receive_message(void *msg, void *cptmsg, void *key, int sock) {
	unsigned char *buffer = msg;
	
	int result = read(sock, cptmsg, MSGSIZE);
	if (result < 0) {
		printf("\n No message received \n");
		return result;
	}
	chat_decrypt(key, cptmsg, MSGSIZE, msg);
	buffer[128] = '\0';
	printf("%s\n", buffer);
	
	return result;
}
