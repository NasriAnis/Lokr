#include <gtk/gtk.h>

#include "../src/include/vault.h"
#include "../src/include/crypto.h"

static void main_window(GtkApplication *app, gpointer data);
static void view_vault(GtkButton *button, gpointer *window_ptr);
GtkWidget* create_credential_row(const char *site, const char *username, const char *password);

typedef struct{
  // GtkWidget *scrolled_window;
  // GtkWidget *scrolled_area;
  GtkWidget *content_area;
  // GtkWidget *sidebar;
  GtkWidget *window;
  // GtkWidget *paned;
} Window;

int show_main_window(int argc, char** argv)
{
  GtkApplication *app;
  app = gtk_application_new("com.lockr.app", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "activate", G_CALLBACK (main_window), NULL);

  int status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

static void main_window(GtkApplication *app, gpointer data)
{
  GtkWidget *paned, *sidebar, *btn_show_all,
  *scrolled_window, *content_area, *main_window;

  Window *window_ptr = g_malloc(sizeof(Window));

  // Initialize window
  main_window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (main_window), "Lokr vault");
  gtk_window_set_default_size (GTK_WINDOW (main_window), 700, 600);

  // initialize the panned box
  paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_window_set_child(GTK_WINDOW(main_window), paned);

  // create a right sidebar inside the panned box + button inside
  sidebar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_size_request(sidebar, 150, -1);
  gtk_paned_set_start_child(GTK_PANED(paned), sidebar);

  btn_show_all = gtk_button_new_with_label("Show All Data");
  g_signal_connect(btn_show_all, "clicked", G_CALLBACK(view_vault), window_ptr);
  gtk_box_append(GTK_BOX(sidebar), btn_show_all);

  // initialize the right scrooled bar for content
  scrolled_window = gtk_scrolled_window_new();
  gtk_paned_set_end_child(GTK_PANED(paned), scrolled_window);

  // Create a box inside the scrolled window to hold password rows
  content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), content_area);

  // save pointers used in other functions
  window_ptr->window = main_window;
  window_ptr->content_area = content_area;
  // window_ptr->scrolled_window = scrolled_window;

  gtk_window_present (GTK_WINDOW (main_window));
}

static void view_vault(GtkButton *button, gpointer *data)
{
  Window *window_ptr = (Window *)data;

  size_t decoded_len = 0;
  Entry *result = NULL;

  result = dump_all("user.bin");

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

    // unsigned char *clear_passwd = crypto_decrypt(
    //     (const unsigned char *)user.passwd, (unsigned char *)decoded_password);

    GtkWidget *content_area = window_ptr->content_area;
    gtk_box_append(GTK_BOX(content_area), create_credential_row(decoded_site,  decoded_username,  "********"));
  }
}

// Helper to create a single row with 3 entry fields
GtkWidget* create_credential_row(const char *site, const char *username, const char *password) {
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
    gtk_entry_set_visibility(GTK_ENTRY(pass_entry), FALSE); // hide chars
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
