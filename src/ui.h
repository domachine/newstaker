#ifndef _UI_H_
#define _UI_H_

#include <gtk/gtk.h>
#include <webkit/webkit.h>

/*
  Gettext support is planned for the future.
*/
#define _(x) x

/*
  Enumeration for easy tree view column access.
*/
enum
  {
    FEED_COLUMN,
    URL_COLUMN,
    N_COLUMNS
  };

struct user_interface
{
  GtkWidget *main_window;

  /*
    The main vertical box that holds
    the top level widgets.
  */
  GtkWidget *vbox;
  GtkWidget *tree_view;

  /*
    The webview that displays the currently
    selected item's content.
  */
  GtkWidget *web_view;

  GtkTreeStore *tree_store;
  WebKitWebFrame *web_frame;
};

typedef struct user_interface ui_t;


/*
  Creates and initilizes a new user interface
  object. But it doesn't show anything.
  This is the job of the module user.
*/
ui_t *
create_user_interface (void);

#endif /* _UI_H_ */
