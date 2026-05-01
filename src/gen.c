#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sodium.h>

#include "include/gen.h"

/* Character sets for different complexities */
static const char CHARSET_LOW[] = "0123456789abcdefghijklmnopqrstuvwxyz";
static const char CHARSET_MEDIUM[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char CHARSET_HIGH[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_=+[]{}|;:,.<>?";

// generate a password into a buffer, return 0 for success
int generate_password(size_t length, PasswordComplexity complexity, char *buffer, size_t buffer_size) {
    if (length < 8 || length > 1024) {
        fprintf(stderr, "Password length must be between 8 and 1024\n");
        return -1;
    }
    
    if (buffer_size < length + 1) {
        fprintf(stderr, "Buffer too small for generated password\n");
        return -1;
    }

    const char *charset = NULL;
    size_t charset_len = 0;

    /* Select character set based on complexity */
    switch (complexity) {
        case COMPLEXITY_LOW:
            charset = CHARSET_LOW;
            charset_len = strlen(CHARSET_LOW);
            break;
        case COMPLEXITY_MEDIUM:
            charset = CHARSET_MEDIUM;
            charset_len = strlen(CHARSET_MEDIUM);
            break;
        case COMPLEXITY_HIGH:
            charset = CHARSET_HIGH;
            charset_len = strlen(CHARSET_HIGH);
            break;
        default:
            fprintf(stderr, "Invalid complexity level\n");
            return -1;
    }

    /* Generate random bytes and map to charset */
    unsigned char random_bytes[length];
    randombytes_buf(random_bytes, length);

    for (size_t i = 0; i < length; i++) {
        buffer[i] = charset[random_bytes[i] % charset_len];
    }
    buffer[length] = '\0';

    return 0;
}

