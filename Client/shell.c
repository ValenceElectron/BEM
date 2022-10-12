#include "client.h"
#include <stdbool.h>

void zero_msg(void *message);

void shell_start(void *key) {
	unsigned char messageCrypt[MSGSIZE] = {0};
	unsigned char buffer[MSGSIZE + 1] = {0};
	
	bool shellLoop = true;
	int shellMode = 0; // 0 is base shell, 1 is messaging
	bool firstTime = false;
	
	char cmd[16];
	
	printf("\n\n");
	printf("-+-----------------------------+-\n");
	printf(" |                             | \n");
	printf(" |  Basic Encrypted Messaging  | \n");
	printf(" |                             | \n");
	printf("-+-----------------------------+-\n\n");
	
	/*if(firstTime) {
		// Do first time setting up here
	}*/
	
	while(shellLoop) {
		printf("BEM> ");
		scanf("%s", cmd);
		printf("\n");
		if(strcmp(cmd, "send") == 0) {
			shellMode = 1;
			while (shellMode == 1) {
				unsigned char message[MSGSIZE - 16] = {0};
				printf("SEND> ");
				scanf("%s", message);
				if (strcmp(message, "exit") == 0) {
					shellMode = 0;
				} else if (strcmp(message, "") == 0) {
					
				} else {
					int client_fd = 0;
					int sock = network_initialize(&client_fd);
					
					if ((send_message(message, messageCrypt, key, sock)) < 0) {
						printf("\n Message could not be sent \n");
					}
					
					network_shutdown(&client_fd);
					bzero(message, sizeof(message));
				}
			}
		}
	}
}
