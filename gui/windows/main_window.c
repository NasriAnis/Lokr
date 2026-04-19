#include <gtk/gtk.h>

static void main_window(GtkApplication *app, gpointer data);
static void view_vault(GtkButton *button, gpointer *window_ptr);

typedef struct{
  GtkWidget *scrolled_window;
  GtkWidget *scrolled_area;
  GtkWidget *content_area;
  GtkWidget *sidebar;
  GtkWidget *window;
  GtkWidget *paned;
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
  content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), content_area);

  // save pointers used in other functions
  window_ptr->window = main_window;

  gtk_window_present (GTK_WINDOW (main_window));
}

static void view_vault(GtkButton *button, gpointer *data)
{
  Window *window_ptr = (Window *)data;
  GtkWidget *main_window = window_ptr->window;

  // GtkWidget *scroll;
  // GtkWidget *list_container;
  // GtkWidget *row;
  // GtkWidget *box;
  //
  // box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  // gtk_window_set_child(GTK_WINDOW(main_window), box);
  // //
  // // label = gtk_label_new("Welcome to Lockr");
  // // gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
  // //
  // // gtk_box_append(GTK_BOX(box), label);
  // //
  // // gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  // // gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  //
  // //Create the scrolled window (gives you the scrollbars)
  // scroll = gtk_scrolled_window_new();
  // gtk_window_set_child(GTK_WINDOW(main_window), scroll);
  // gtk_widget_set_vexpand(scroll, TRUE);
  //
  // //Create the vertical box that will hold all your rows
  // list_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  // gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), list_container);
  //
  // //To add a row (do this inside a loop of your results):
  // row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
  // GtkWidget *service_label = gtk_label_new("GitHub");
  // GtkWidget *pass_label = gtk_label_new("********");
  //
  // gtk_box_append(GTK_BOX(row), service_label);
  // gtk_box_append(GTK_BOX(row), pass_label);
  //
  // // Add the row to your main list container
  // gtk_box_append(GTK_BOX(list_container), row);
  //
  // gtk_window_present (GTK_WINDOW (main_window));
}
