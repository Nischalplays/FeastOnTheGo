#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <gtk/gtk.h>


GtkWidget *createProductPage();
// void create_category(Category *category);
// void get_category(GtkWidget *comboBox, Category *category);

extern GtkWidget *categoryTopContainer;
extern int categoryEmpty;
extern GtkWidget *categoryContent;

#endif // !PRODUCTS_H