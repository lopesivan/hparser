/*============================================================================*\
 *'hparser' examples.                                                         *
 *Copyright (C) 2007-2008 Kevin P. Barry (ta0kira@users.sourceforge.net)      *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#ifndef GTK_PROXY_HPP
#define GTK_PROXY_HPP

#include <hparser/impl-defined.hpp>
#include <gtk/gtk.h>

//This class is used as a function argument in 'hparser' classes, however its
//use and definition are entirely up to the implementation for versatility.
//This implementation-defined class is intended to be used as a conduit between
//GUI elements of an 'hparser' structure.
struct element_interface
{
  virtual GtkWidget *CurrentGUI() const   = 0;
  virtual GtkWidget *RegenerateGUI()      = 0;
  virtual GtkWidget *GUIContainer() const = 0;
  virtual void       ClearGUI()           = 0;

  virtual inline ~element_interface() {}
};

//GTK components for a main window
typedef struct MainView
{
  GtkWidget *Window;
  GtkWidget *Viewport;
  GtkWidget *Container;
};

//Element switching function for GTK callback events
extern void SwitchFunction(void*, gpointer);

//Specific GTK components for the main window
extern MainView GlobalView;

#endif
