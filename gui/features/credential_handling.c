#include <gtk/gtk.h>

#include "../include/cred.h"
#include "../include/main_window.h"

#include "../../src/include/crypto.h"
#include "../../src/include/vault.h"

typedef struct{
  GtkWidget *entry_username;
  GtkWidget *entry_password;
  GtkWidget *entry_site;
} entry_ptr;

static void save_password(GtkButton *button2, gpointer *data);

void add_password_window(GtkButton *button2, gpointer *data){
  GtkWidget *box;
  GtkWidget *label;
  GtkWidget *button;

  Window *window_ptr = (Window *)data;
  GtkWidget *add_pass_area = window_ptr->add_pass_area;
  gtk_stack_set_visible_child_name(GTK_STACK(window_ptr->stack), "add_pass");

  // clear old form if button clicked multiple times
  GtkWidget *child;
  while ((child = gtk_widget_get_first_child(add_pass_area)) != NULL) {
    gtk_box_remove(GTK_BOX(add_pass_area), child);
  }

  entry_ptr *entry = g_malloc(sizeof(entry_ptr));

  /* Create a box */
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(add_pass_area), box);

  /* Create site entry */
  label = gtk_label_new("site");
  gtk_widget_set_halign(label, GTK_ALIGN_START);
  gtk_box_append(GTK_BOX(box), label);

  entry->entry_site = gtk_entry_new();
  gtk_box_append(GTK_BOX(box), entry->entry_site);

  /* Create user entry */
  label = gtk_label_new("username");
  gtk_widget_set_halign(label, GTK_ALIGN_START);
  gtk_box_append(GTK_BOX(box), label);

  entry->entry_username = gtk_entry_new();
  gtk_box_append(GTK_BOX(box), entry->entry_username);

  /* Create password entry */
  label = gtk_label_new("password");
  gtk_widget_set_halign(label, GTK_ALIGN_START);
  gtk_box_append(GTK_BOX(box), label);

  entry->entry_password = gtk_entry_new();
  gtk_box_append(GTK_BOX(box), entry->entry_password);

  /* Create a button */
  button = gtk_button_new_with_label("add");
  g_signal_connect(button, "clicked", G_CALLBACK(save_password), entry);
  gtk_box_append(GTK_BOX(box), button);
}

static void save_password(GtkButton *button2, gpointer *data){
  entry_ptr *entry = (entry_ptr *)data;

  const char *site = gtk_editable_get_text(GTK_EDITABLE(entry->entry_site));
  const char *username = gtk_editable_get_text(GTK_EDITABLE(entry->entry_username));
  const char *password = gtk_editable_get_text(GTK_EDITABLE(entry->entry_password));

  size_t blob_len = 0;
  unsigned char *encrypted_pass =
    crypto_encrypt((unsigned char *)global_credentials.password, (unsigned char *)password, strlen(password), &blob_len);

  char *b64_site = encode_base64((char *)site);
  char *b64_login = encode_base64((char *)username);
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

  gtk_editable_set_text(GTK_EDITABLE(entry->entry_site), "");
  gtk_editable_set_text(GTK_EDITABLE(entry->entry_username), "");
  gtk_editable_set_text(GTK_EDITABLE(entry->entry_password), "");
}
