#include "../client.h"

void OpenKey(void *buf) {
	unsigned char *bufp = buf;
	unsigned char key[32];
	FILE *fileP;
	fileP = fopen("key", "rb+");
	if (fileP == NULL) {
		printf("Could'nt open up key file\n");
	}
	
	fread(key, sizeof(key), 1, fileP);
	for (int i = 0; i < 32; i++) {
		bufp[i] = key[i];
	}
	
	ClearKey(key);
}

void ClearKey(void *buf) {
	unsigned char *buffer = buf;
	for (int i = 0; i < 32; i++) {
		buffer[i] = i;
	}
}
