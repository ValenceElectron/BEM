#include <stdio.h>
#include <string.h>
#include <stdlib.h>

# if 0			// Set to 1 when need to write key.
int main(int argc, char const* argv[]) {
	// 32-bit key.
	unsigned char key[32] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
						  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
	
	FILE *keyF;
	keyF = fopen("key", "wb+");
	for (int i = 0; i < 32; i++) {
		fwrite(&key[i], sizeof(key[i]), 1, keyF);
	}
}

#endif

# if 1			// Set to 1 when need to read key.
int main(int argc, char const* argv[]) {
	unsigned char key[32];
	
	FILE *keyF;
	keyF = fopen("key", "rb+");
	fread(key, sizeof(key), 1, keyF);
	
	for (int i = 0; i < 32; i++) {
		printf("%2x ", key[i]);
	}
}

#endif
