#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/auth.h"
#include "include/crypto.h"
#include "include/vault.h"


int authenticate(char *password_buffer, char* username_buffer) {
  char* encoded_saved_pass;
  char* decoded_saved_pass;
  char* saved_username;
  char* de_saved_username;
  char** b64_raw_value;
  int flag = 0;

  b64_raw_value = Cred_search("user.bin");
  saved_username = b64_raw_value[0];
  encoded_saved_pass = b64_raw_value[1];

  decoded_saved_pass = decode_base64(encoded_saved_pass);
  de_saved_username = decode_base64(saved_username);

  if (strcmp(username_buffer, de_saved_username) != 0){
    printf("wrong user.\n");
    flag = 1;
  }
  if (verify_password(password_buffer, decoded_saved_pass) != 0){
      printf("wrong password\n");
    flag = 1;
  }

  free(b64_raw_value);
  free(encoded_saved_pass);
  free(de_saved_username);

  if (flag != 0){
    return 1;
  } else { return 0; }
}

// Create and save a user to the data base
void create_user(char* username, char* password) {
  char* b64_username;
  char* b64_password;

  // hash the password : encoded
  char hash_pass[ENCODED_LEN];
  hash_password(password, hash_pass);

  b64_username = encode_base64(username);
  b64_password = encode_base64(hash_pass);
 
  // save user
  F_write("user.bin", b64_username, 0);
  F_write("user.bin", " ", 0);
  F_write("user.bin", b64_password, 1);
  printf("User created and saved.\n");

  free(b64_username);
  free(b64_password);
}
