#include <gtk/gtk.h>
#include <stdio.h>

#include "../../src/include/vault.h"
#include "../../src/include/crypto.h"

#include "../include/cred.h"
#include "../include/main_window.h"
#include "../include/view_vault.h"

GtkWidget* create_credential_row(const char *site, const char *username, const char *password);

void view_vault_window(GtkButton *button, gpointer *data){
  size_t decoded_len = 0;
  Entry *result = NULL;
  GtkWidget *child;

  Window *window_ptr = (Window *)data;
  GtkWidget *content_area = window_ptr->content_area;

  gtk_stack_set_visible_child_name(GTK_STACK(window_ptr->stack), "vault");

  result = dump_all("user.bin");

  if (result == NULL) {
    printf("Error: Not found\n");
    return;
  }

  while ((child = gtk_widget_get_first_child(content_area)) != NULL) {
    gtk_box_remove(GTK_BOX(content_area), child);
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
    unsigned char *decoded_password = decode_base64_bin(result[j].password, &decoded_len);

    // retrieve key from global struct
    char *key = global_credentials.password;
    unsigned char *clear_passwd = crypto_decrypt( (const unsigned char *)key, (unsigned char *)decoded_password);

    gtk_box_append(GTK_BOX(content_area), create_credential_row(decoded_site,  decoded_username,  (char *)clear_passwd));

    free(decoded_site);
    free(decoded_username);
    free(decoded_password);
    free(clear_passwd);
  }
  free(result);
}

// Helper to create a single row with 3 entry fields
GtkWidget* create_credential_row(const char *site, const char *username, const char *password){
    // Outer row container
    GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_margin_start(row, 8);
    gtk_widget_set_margin_end(row, 8);
    gtk_widget_set_margin_top(row, 4);
    gtk_widget_set_margin_bottom(row, 4);

    // --- Site field ---
    GtkWidget *site_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    // GtkWidget *site_label = gtk_label_new("Site");
    GtkWidget *site_entry = gtk_entry_new();
    gtk_widget_set_hexpand(site_entry, TRUE); // stretch to fill space
    if (site)
        gtk_editable_set_text(GTK_EDITABLE(site_entry), site);
    // gtk_box_append(GTK_BOX(site_box), site_label);
    gtk_box_append(GTK_BOX(site_box), site_entry);
    gtk_widget_set_hexpand(site_box, TRUE);

    // --- Username field ---
    GtkWidget *user_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    // GtkWidget *user_label = gtk_label_new("Username");
    GtkWidget *user_entry = gtk_entry_new();
    gtk_widget_set_hexpand(user_entry, TRUE);
    if (username)
        gtk_editable_set_text(GTK_EDITABLE(user_entry), username);
    // gtk_box_append(GTK_BOX(user_box), user_label);
    gtk_box_append(GTK_BOX(user_box), user_entry);
    gtk_widget_set_hexpand(user_box, TRUE);

    // --- Password field ---
    GtkWidget *pass_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    // GtkWidget *pass_label = gtk_label_new("Password");
    GtkWidget *pass_entry = gtk_entry_new();
    // gtk_entry_set_visibility(GTK_ENTRY(pass_entry), FALSE); // hide chars
    gtk_widget_set_hexpand(pass_entry, TRUE);
    if (password)
        gtk_editable_set_text(GTK_EDITABLE(pass_entry), password);
    // gtk_box_append(GTK_BOX(pass_box), pass_label);
    gtk_box_append(GTK_BOX(pass_box), pass_entry);
    gtk_widget_set_hexpand(pass_box, TRUE);

    // Pack all three into the row
    gtk_box_append(GTK_BOX(row), site_box);
    gtk_box_append(GTK_BOX(row), user_box);
    gtk_box_append(GTK_BOX(row), pass_box);

    return row;
}
