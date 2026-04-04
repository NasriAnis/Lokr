#ifndef CRYPTO_H
#define CRYPTO_H

#include <stddef.h>

#define HASH_LEN 32
#define ENCODED_LEN 128

int verify_password(const char *password, const char *encoded);
int hash_password(const char *password, char encoded[ENCODED_LEN]);
unsigned char* crypto_encrypt(const unsigned char *key, const unsigned char *message, size_t message_len);
unsigned char* crypto_decrypt(const unsigned char *key, unsigned char* blob);
char* encode_base64(const char* bin);
char* decode_base64(const char* b64);

#endif
