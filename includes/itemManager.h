#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <gtk/gtk.h>
#include "structManager.h"

extern GtkWidget *defaultLoadBox;

extern char *dataFilePath;
extern char *addItemDefaultImage;

void addItemToBox(GtkButton *button, gpointer user_data);
void on_file_set(GtkFileChooserButton *filebutton, gpointer userdata);
GtkWidget *create_box(gpointer user_data);
void updata_image(char *newImagePath, gpointer user_data);
void on_submit(GtkButton *current_button, gpointer user_data);
GtkWidget *load_box(GtkWidget *boxToLoad, gpointer user_data);
void loadItemBox(Products *product);

#endif // !ITEMMANAGER_H