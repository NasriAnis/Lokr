#include <gtk/gtk.h>

#include "include/login_window.h"
#include "include/signup_window.h"
#include "include/main_window.h"

#include "../src/include/vault.h"

int main()
{
  int flag;
  if (F_exist("user.bin") != 0) {
    flag = show_signup_panel(0, NULL);
  } else {
    flag = show_login_panel(0, NULL);
  }
  if (flag == 0){
    show_main_window(0, NULL);
  }
  return 0;
}
