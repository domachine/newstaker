
#include "ui.h"


static const gchar* form_markup =
  "Das ist ein <b>Test</b>";

static void
init_web_view (ui_t *ui);

static void
init_tree_view (ui_t *ui);


ui_t *
create_user_interface (void)
{
  GtkWidget *scrolled_window;
  ui_t *ui;

  ui = (ui_t *) g_malloc (sizeof (ui_t));

  ui->main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (ui->main_window), "Newstaker");
  gtk_window_set_default_size (GTK_WINDOW (ui->main_window), 640, 240);

  ui->vbox = gtk_vbox_new (TRUE, 1);
  gtk_container_add (GTK_CONTAINER (ui->main_window), ui->vbox);

  /*
    Build tree view enclosed in a scrolled window.
  */
  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  init_tree_view (ui);
  gtk_container_add (GTK_CONTAINER (scrolled_window), ui->tree_view);

  gtk_box_pack_start (GTK_BOX (ui->vbox), scrolled_window, TRUE, TRUE, 0);

  /*
    The scrolled window in which we will place the webkit
    browser to display the html.
  */
  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  init_web_view (ui);
  gtk_container_add (GTK_CONTAINER (scrolled_window), ui->web_view);

  /* g_object_unref (G_OBJECT (ui->web_view)); */

  gtk_box_pack_start (GTK_BOX (ui->vbox), scrolled_window, TRUE, TRUE, 0);

  return ui;
}

void
init_tree_view (ui_t *ui)
{
  GtkTreeViewColumn *tree_view_column;
  GtkCellRenderer *cell_renderer;
  GtkTreeIter tree_iter, child;

  ui->tree_store = gtk_tree_store_new (N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING);
  ui->tree_view = gtk_tree_view_new_with_model (GTK_TREE_MODEL (ui->tree_store));

  cell_renderer = gtk_cell_renderer_text_new ();
  tree_view_column = gtk_tree_view_column_new_with_attributes (_("Feed"), cell_renderer,
                                                               "text", FEED_COLUMN, NULL);
  gtk_tree_view_append_column (GTK_TREE_VIEW (ui->tree_view), tree_view_column);

  tree_view_column = gtk_tree_view_column_new_with_attributes (_("Url"), cell_renderer,
                                                               "text", URL_COLUMN, NULL);
  gtk_tree_view_append_column (GTK_TREE_VIEW (ui->tree_view), tree_view_column);

  /*
    Add some test entries.
  */
  gtk_tree_store_append (ui->tree_store, &tree_iter, NULL);
  gtk_tree_store_set (ui->tree_store, &tree_iter,
                      FEED_COLUMN, "Heise",
                      URL_COLUMN, "http://www.heise.de/rss",
                      -1);

  gtk_tree_store_append (ui->tree_store, &child, &tree_iter);
  gtk_tree_store_set (ui->tree_store, &child,
                      FEED_COLUMN, "SAP übernimmt Unternehmen",
                      URL_COLUMN, "http://www.heise.de/post/12334",
                      -1);
}

void
init_web_view (ui_t *ui)
{
  ui->web_view = webkit_web_view_new ();

  /*
    Load simple test page.
  */
  webkit_web_view_load_string (WEBKIT_WEB_VIEW (ui->web_view),
                               form_markup, "text/html", "UTF-8", "");
}
