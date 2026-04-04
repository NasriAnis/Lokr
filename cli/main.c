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

void user_creation();
void authentication();
void add(char* tokens[]);
// void show();

int main(int argc, char *argv[]) {

  // if no argument are specififed
  if (argc < 2) {
    // check credentials

    if (F_exist("user.bin") != 0) {
      user_creation();
    }
    else {
      authentication();
    }

    // save credential to a struct
    str_cpy(user.username, username_buffer);
    str_cpy(user.passwd, password_buffer); // the password will be used as an encryption key

    while (1){
      printf("> ");
      fgets(user_input, sizeof(user_input), stdin);
      int count = tokenize(user_input, tokens);

      if (strcmp(tokens[0], "add") == 0){
        if (count != 4){
          printf("Command layout : add [site] [username] [pasword]");
        } else { add(tokens); }
      }
      else if (strcmp(tokens[0], "show") == 0){
        // show();
      }
    }
  }

  // if arguments are specified
  else {
  printf("Runnig with argument : %s\n", argv[2]);
  }
  return 0;
}

void user_creation(){
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
void authentication(){
  do {

    printf("Enter your username : ");
    f_gets(username_buffer);
    trim(username_buffer);

    printf("Enter your password : ");
    f_gets(password_buffer);
    trim(password_buffer);

  } while (authenticate(password_buffer, username_buffer) != 0);
}

void add(char* tokens[]){
  char *site = tokens[1];
  char *login = tokens[2];
  char *pass = tokens[3];

  printf("Do you wanna add this account to the database ?\n");
  printf("Site : %s\n", site);
  printf("User : %s\n", login);
  printf("Password : %s\n", pass);

  printf("(Y/n) : ");
  fgets(user_input, sizeof(user_input), stdin);

  if (strcmp(user_input, "n")!=0){
    unsigned char* encrypted_pass =
                  crypto_encrypt((unsigned char *)user.passwd,
                                 (unsigned char *)pass,
                                           sizeof(pass));

    char* b64_site = encode_base64(site);
    char* b64_login = encode_base64(login);
    char* b64_pass = encode_base64((const char*)encrypted_pass);

    F_write("user.bin", b64_site, 0);
    F_write("user.bin", " ", 0);
    F_write("user.bin", b64_login, 0);
    F_write("user.bin", " ", 0);
    F_write("user.bin", b64_pass, 1);

    free(encrypted_pass);
    free(b64_site);
    free(b64_pass);
    free(b64_login);

  }
}

// void show(){
//   char *site = tokens[1];
//   char *login = tokens[2];
//
//   char line[100];
//   F_search("user.bin", site, line, 1);
//   printf("%s", line);
// }
