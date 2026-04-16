#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/include/auth.h"
#include "../src/include/crypto.h"
#include "../src/include/misc.h"
#include "../src/include/vault.h"

typedef struct {
  char username[70];
  char passwd[70];
} user_t;
user_t user;

char password_buffer[1060];
char username_buffer[1060];
char user_input[1020];

void user_creation();
void authentication();
void add(char *tokens[]);
void show(char *tokens[]);

int main(int argc, char *argv[]) {

  char *tokens[64];

  // if no argument are specififed
  if (argc < 2) {
    // check credentials

    if (F_exist("user.bin") != 0) {
      user_creation();
    } else {
      authentication();
    }

    // save credential to a struct
    str_cpy(user.username, username_buffer);
    str_cpy(user.passwd,
            password_buffer); // the password will be used as an encryption key

    while (1) {
      printf("> ");
      fgets(user_input, sizeof(user_input), stdin);
      int count = tokenize(user_input, tokens);

      if (strcmp(tokens[0], "add") == 0) {
        if (count != 4) {
          printf("Command layout : add [site] [username] [pasword]");
        } else {
          add(tokens);
        }
      } else if (strcmp(tokens[0], "show") == 0) {
        if (count != 2) {
          printf("Command layout : add site=[site] or add user=[username]");
        } else {
          show(tokens);
        }
      }
    }
  }

  // if arguments are specified
  else {
    printf("Runnig with argument : %s\n", argv[2]);
  }
  return 0;
}

void user_creation() {
  // Takes user credential
  printf("please create a user.\n");

  printf("Username : ");
  f_gets(username_buffer);
  trim(username_buffer);

  printf("Password : ");
  f_gets(password_buffer);
  trim(password_buffer);

  create_user(username_buffer, password_buffer);
}
void authentication() {
  do {

    printf("Enter your username : ");
    f_gets(username_buffer);
    trim(username_buffer);

    printf("Enter your password : ");
    f_gets(password_buffer);
    trim(password_buffer);

  } while (authenticate(password_buffer, username_buffer) != 0);
}

void add(char *tokens[]) {
  char *site = tokens[1];
  char *login = tokens[2];
  char *pass = tokens[3];

  printf("Do you wanna add this account to the database ?\n");
  printf("Site : %s\n", site);
  printf("User : %s\n", login);
  printf("Password : %s\n", pass);

  printf("(Y/n) : ");
  fgets(user_input, sizeof(user_input), stdin);

  if (strcmp(user_input, "n") != 0) {
    size_t blob_len = 0;
    unsigned char *encrypted_pass =
        crypto_encrypt((unsigned char *)user.passwd, (unsigned char *)pass,
                       strlen(pass), &blob_len);

    char *b64_site = encode_base64(site);
    char *b64_login = encode_base64(login);
    char *b64_pass = encode_base64_bin((char *)encrypted_pass, blob_len);

    F_write("user.bin", b64_site, 0);
    F_write("user.bin", " ", 0);
    F_write("user.bin", b64_login, 0);
    F_write("user.bin", " ", 0);
    F_write("user.bin", b64_pass, 1);

    free(encrypted_pass);
    free(b64_login);
    free(b64_site);
    free(b64_pass);
  }
}

void show(char *tokens[]) {
  // check if the tokens contains "="
  int flag = 0;
  int len = strlen(tokens[1]);

  int i;
  for (i = 0; len >= i; i++) {
    if (tokens[1][i] == '=') {
      flag = 1;
    }
  }

  if (flag != 1){
    printf("Syntax error expected : \
           show site=[site] or show user=[username]");
    return;
  }

  Entry *result = NULL;
  char *key = strtok(tokens[1], "=");
  char *value = strtok(NULL, "=");

  size_t decoded_len = 0;

  char *b_key1 = encode_base64(value);

  if (strcmp(key, "site") == 0) {
    result = search("user.bin", b_key1, 1);
  }
  else if (strcmp(key, "user") == 0) {
    result = search("user.bin", b_key1, 2);
  }
  else {
    printf("Syntax error expected : \
           show site=[site] or show user=[username]");
  }

  if (result == NULL) {
    printf("Error: Not found\n");
    return;
  }
 
 // logic change loop throught 3 words at a time
  int j;
  for (j = 0; 1; j++){

    // check for sentinel
    if (result[j].site == NULL \
      && result[j].username == NULL \
      && result[j].password == NULL){
      break;
    }

    char *decoded_site = decode_base64(result[j].site);
    char *decoded_username = decode_base64(result[j].username);
    unsigned char *decoded_password =
        decode_base64_bin(result[j].password, &decoded_len);

    unsigned char *clear_passwd = crypto_decrypt(
        (const unsigned char *)user.passwd, (unsigned char *)decoded_password);

    printf("%s %s %s", decoded_site, decoded_username, clear_passwd);
  }

  free(b_key1);
  free(result);
}
