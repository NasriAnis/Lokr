#include <argon2.h>
#include <sodium.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "crypto.h"

#define CIPHERTEXT_LEN (crypto_secretbox_MACBYTES + MESSAGE_LEN)
#define MESSAGE_LEN 4

#define ui32 uint32_t

// Hash the password and return success value
int hash_password(const char *password, char encoded[ENCODED_LEN]) {
  unsigned char salt[16] = {0};
  int rc = argon2id_hash_encoded(2,       // time cost (iterations)
                                 1 << 16, // memory cost (64 MB)
                                 1,       // parallelism
                                 password, strlen(password), salt, sizeof(salt),
                                 HASH_LEN, encoded, ENCODED_LEN);
  return rc == ARGON2_OK ? 0 : -1;
}

// Verify a password against a stored hash
int verify_password(const char *password, const char *encoded) {
  int rc = argon2id_verify(encoded, password, strlen(password));
  return rc == ARGON2_OK ? 0 : -1; // 0 = match
}

unsigned char *crypto_encrypt(const unsigned char *key, const unsigned char *message, size_t message_len) {

  size_t ctext_len = crypto_secretbox_MACBYTES + message_len;
  size_t blob_len  = crypto_secretbox_NONCEBYTES + ctext_len + sizeof(ui32);

  unsigned char *blob = malloc(blob_len);
  if (!blob){ return NULL; }

  // save message lenght
  ui32 len32 = (ui32)message_len;
  memcpy(blob, &len32, sizeof(ui32));

  // unsigned char *nonce = out_blob;
  unsigned char* nonce = blob + sizeof(ui32);
 
  // unsigned char *ciphertext = out_blob + crypto_secretbox_NONCEBYTES;
  unsigned char* ctext = blob + crypto_secretbox_NONCEBYTES + sizeof(ui32);

  randombytes_buf(nonce, crypto_secretbox_NONCEBYTES);
  crypto_secretbox_easy(ctext, message, message_len, nonce, key);

  printf("ciph = %s \n nonce = %s \n", ctext, nonce);

  return blob;
}

unsigned char* crypto_decrypt(const unsigned char *key, unsigned char* blob){

  // size_t* message_len;
  // memcpy(message_len, blob, sizeof(ui32));
  uint32_t len32;
  memcpy(&len32, blob, sizeof(uint32_t));
  size_t message_len = (size_t)len32;

  const unsigned char* nonce = blob + sizeof(ui32);
  const unsigned char* ctext = blob + crypto_secretbox_NONCEBYTES + sizeof(ui32);

  size_t ctext_len = crypto_secretbox_MACBYTES + message_len;
  size_t blob_len  = crypto_secretbox_NONCEBYTES + ctext_len;

  unsigned char* plain_text = malloc(message_len + 1);
  if (!plain_text){ return NULL; }

  printf("ciph = %s \n nonce = %s \n", ctext, nonce);

  if (crypto_secretbox_open_easy(plain_text, ctext, ctext_len, nonce, key) != 0){
    free(plain_text);
    fprintf(stderr, "Decryption failed");
    return NULL;
  }
 
  plain_text[message_len] = '\0';
  return plain_text;
}
