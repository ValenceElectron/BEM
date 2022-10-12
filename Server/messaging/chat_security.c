// chat_security.c by Anthony Alaman (AnthonyAlaman@csus.edu). Submitted for CSC 152 October 9th, 2022.
// Implements AES256-CTR encryption as requested in the Program 4 homework
// Referenced https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption for encryption and decryption.

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void chat_encrypt(void *k, void *pt, int ptlen, void *ct) {
	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
	int len;
	int bytes_written = 0;
	unsigned char iv[32];
	
	unsigned char buf[112];
	
	RAND_bytes(iv, 16);
	for (int i = 16; i < 32; i++) {
		iv[i] = '0';
	}
	
	EVP_EncryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, k, iv);
	EVP_EncryptUpdate(ctx, buf, &len, pt, ptlen);
	bytes_written += len;
	EVP_EncryptFinal_ex(ctx, buf + bytes_written, &len);
	bytes_written += len;
	EVP_CIPHER_CTX_free(ctx);
	
	unsigned char *ctp = ct;
	for (int i = 0; i < 16; i++) {
		ctp[i] = iv[i];
	}
	for (int i = 16; i < 128; i++) {
		ctp[i] = buf[i - 16];
	}
}

void chat_decrypt(void *k, void *ct, int ctlen, void *pt) {
	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
	
	unsigned char *ctp = ct;
	int newctlen = ctlen - 16;
	unsigned char ctnew[newctlen];
	for (int i = 0; i < newctlen; i++) {
		ctnew[i] = ctp[i+16];
	}
	
	unsigned char iv[32] = {0};
	for (int i = 0; i < 16; i++) {
		iv[i] = ctp[i];
	}
	for (int i = 0; i < 16; i++) {
		iv[i+16] = '0';
	}
	
	int len;
	int bytes_written = 0;
	
	EVP_DecryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, k, iv);
	EVP_DecryptUpdate(ctx, pt, &len, ctnew, newctlen);
	bytes_written += len;
	EVP_DecryptFinal_ex(ctx, pt + bytes_written, &len);
	bytes_written += len;
	EVP_CIPHER_CTX_free(ctx);
}

# if 0		// Set to 1 while testing and 0 for submission
#include <stdio.h>
int main() {
	// Test code here
	unsigned char key[32] = {0};
	unsigned char plaintext[101] = "The quick brown fox jumped over the lazy dog";
	unsigned char cryptedtext[112] = {0};
	chat_encrypt(key, plaintext, 100, cryptedtext);
	
	printf("Cipher text is: \n");
	BIO_dump_fp(stdout, (const char *) cryptedtext, 112);
	
	chat_decrypt(key, cryptedtext, 112, plaintext);
	
	plaintext[100] = '\0';
	printf("Decrypted text is: \n");
	printf("%s\n", plaintext);
	
	return 0;
}
#endif
