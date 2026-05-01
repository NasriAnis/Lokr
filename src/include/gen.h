#ifndef GEN_H
#define GEN_H

#include <stddef.h>

/* Password complexity levels */
typedef enum {
    COMPLEXITY_LOW = 1,      /* Numbers + lowercase */
    COMPLEXITY_MEDIUM = 2,   /* Numbers + lowercase + uppercase */
    COMPLEXITY_HIGH = 3      /* Numbers + lowercase + uppercase + symbols */
} PasswordComplexity;

/**
 * Generate a random password
 * @param length: Desired password length (minimum 8)
 * @param complexity: Password complexity level
 * @param buffer: Output buffer for generated password
 * @param buffer_size: Size of output buffer
 * @return: 0 on success, -1 on error
 */
int generate_password(size_t length, PasswordComplexity complexity, char *buffer, size_t buffer_size);

#endif
