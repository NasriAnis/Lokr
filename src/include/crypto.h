#ifndef CRYPTO_H
#define CRYPTO_H

#include <stddef.h>

#define HASH_LEN 32
#define ENCODED_LEN 128

char* encode_base64(char* bin);
char* decode_base64(const char* b64);
char* encode_base64_bin(const char* bin, size_t bin_len);
unsigned char* decode_base64_bin(const char* b64, size_t *out_len);

int verify_password(const char *password, const char *encoded);
int hash_password(const char *password, char encoded[ENCODED_LEN]);

unsigned char* crypto_decrypt(const unsigned char *key, unsigned char* blob);
unsigned char* crypto_encrypt(const unsigned char *key, \
    const unsigned char *message, size_t message_len, size_t *blob_len);

#endif
