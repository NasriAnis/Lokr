#include <stdio.h>
#include <string.h>

#include "../src/misc/include/helper.h"
#include "../src/misc/include/wrapper.h"

#include "../src/vault/include/vault_helper.h"

#include "../src/init/include/cred_init.h"

#include "include/help.h"
#include "include/authentication.h"
#include "include/password_handling.h"

int main() {
  // initialize credentials space
  cred_init();

  char password_buffer[1080];
  char username_buffer[1080];
  char user_input[1080];
  char *tokens[64];

  // check credentials
  if (F_exist("user.bin") != 0) {
    user_creation(username_buffer, password_buffer, sizeof(username_buffer), sizeof(password_buffer));
  } else {
    authentication(username_buffer, password_buffer, sizeof(username_buffer), sizeof(password_buffer));
  }

  // save credential to a struct, the password will be used as an encryption key
  str_cpy(global_credentials.username, username_buffer, sizeof(global_credentials.username));
  str_cpy(global_credentials.password, password_buffer, sizeof(global_credentials.username));

  printf("enter 'help' on guidance to use this CLI application\n");
  while (1) {
    printf("> ");
    f_gets(user_input, sizeof(user_input));

    if (strcmp(user_input, "")==0){
      continue;
    }
    int count = tokenize(user_input, tokens);

    if (strcmp(tokens[0], "add") == 0) {
      if (count != 4) {
        printf("Command layout : add [site] [username] [pasword]\n");
      } else {
        add(tokens);
      }
    }

    else if (strcmp(tokens[0], "gen") == 0) {
      if (count != 3) {
        printf("Command layout : gen [site] [username]\n");
      } else {
        gen(tokens);
      }
    }

    else if (strcmp(tokens[0], "show") == 0) {
      if (count != 2) {
        printf("Command layout : show site=[site] or add user=[username]\n");
      } else {
        show(tokens);
      }
    }

    else if (strcmp(tokens[0], "dump-all") == 0){
      dump("user.bin");
    }

    else if (strcmp(tokens[0], "delete") == 0){
      if (count != 3){
        printf("Command layout : delete [site] [username]\n");
        printf("It is recommanded to search for the excat password firdt using the 'show' command !\n");
      }
      else {
        delete(tokens);
      }
    }

    else if (strcmp(tokens[0], "help") == 0){
      help();
    }

    else if(strcmp(tokens[0], "exit") == 0){
      break;
    }

    else {
      printf("Use the `help` command to list available commands.\n");
    }

  }

  cred_cleanup();
  return 0;
}

