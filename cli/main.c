#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auth.h"
#include "vault.h"
#include "misc.h"
#include "crypto.h"

char *tokens[64];
char password_buffer[60];
char username_buffer[60];
char user_input[20];
user_t user;

void add(char* site, char* login, char* encrypted_pass);

int main(int argc, char *argv[]) {

  // if no user file exists prompt to create a user
  if (F_exist("user.bin") != 0) {

    // Takes user credential
    printf("please create a user.\n");
    printf("Username : ");
    f_gets(username_buffer);

    printf("Password : ");
    f_gets(password_buffer);
    create_user(username_buffer, password_buffer);
  }

  // if no argument are specififed
  if (argc < 2) {
    // check credentials
    do {

      printf("Enter your username : ");
      f_gets(username_buffer);

      printf("Enter your password : ");
      f_gets(password_buffer);

    } while (authenticate(password_buffer, username_buffer) != 0);

    // save credential to a struct
    str_cpy(user.username, username_buffer);
    str_cpy(user.passwd, password_buffer); // the password will be used as an encryption key

    while (1){
      printf("> ");
      fgets(user_input, sizeof(user_input), stdin);
      int count = tokenize(user_input, tokens);

      if (strcmp(tokens[0], "add") == 0){

        char *site = tokens[1];
        char *login = tokens[2];
        char *pass = tokens[3];

        printf("Do you wanna add this account to the database ?\n");
        printf("Site : %s\n", site);
        printf("User : %s\n", login);
        printf("Password : %s\n", pass);

        printf("Y/n");
        fgets(user_input, sizeof(user_input), stdin);

        if (strcmp(user_input, "n")!=0){
          unsigned char* encrypted_pass = crypto_encrypt((unsigned char *)user.passwd, (unsigned char *)pass, sizeof(pass)); // dont forget to free the result
          void add(char* site, char* login, char* encrypted_pass);
          free(encrypted_pass);

          unsigned char* plain = crypto_decrypt((unsigned char *)user.passwd, encrypted_pass);
          printf("\ndecrypted = %s\n", plain);
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

void add(char* site, char* login, char* encrypted_pass){

          F_write("user.bin", "site ", 0);
          F_write("user.bin", site, 0);
          F_write("user.bin", " | login ", 0);
          F_write("user.bin", login, 0);
          F_write("user.bin", " | pass ", 0);
          F_write("user.bin", (char *)encrypted_pass, 1);
}
