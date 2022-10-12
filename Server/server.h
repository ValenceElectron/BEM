#ifndef server_h
#define server_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define MSGSIZE 128

void chat_encrypt(void *k, void *pt, int ptlen, void *ct);
void chat_decrypt(void *k, void *ct, int ctlen, void *pt);
void OpenKey(void *buf);
void ClearKey(void *buf);
int send_message(void *msg, void *cptmsg, void *key, int sock);
int receive_message(void *msg, void *cptmsg, void *key, int sock);

#endif
