#ifndef WIDGETMANAGER_H
#define WIDEGTMANAGER_H

#include <gtk/gtk.h>
#include "products.h"
#include "structManager.h"

typedef enum
{
    LOAD,
    SAVE
} WidgetType;

typedef struct 
{
    int response;
} DialogResponse;


GtkWidget *createBox_with_text(int boxWidth, int boxHeight, const char *text, GtkOrientation orientation, const char *widgetName);
GtkWidget *createButton_with_text(int boxWidth, int boxHeight, const char *text);
GtkWidget *createCategoryWindow();
int warningManager(GtkWidget *destinationWindow, GtkButtonsType buttonType, GtkMessageType messageType ,const char *warningText);
GdkPixbuf * createRoundedPixbuf(GdkPixbuf *src, int radius);
GtkWidget *createRoundedImage(const char *filepath, int width, int height, int radius);
gboolean onHover (GtkWidget *widget, GdkEventCrossing *event, gpointer user_data);
gboolean onLeave (GtkWidget *widget, GdkEventCrossing *event, gpointer user_data);
void deleteItemWidget(GtkWidget *widget, gpointer userdata);
GtkWidget *createCategoryBox(GtkWidget *destToCreate, WidgetType type, const char *CategoryName, int index);
void onAddCategory(GtkWidget *button, gpointer user_data);
GtkWidget *createCategoryButton(GtkWidget *destinationToCreate, char *categoryName);
void categoryOption(GtkComboBoxText *comboBox);
void insertIntoCategoryContainer(char *name);
GtkWidget *searchCategoryContainer(char *categoryName);

#endif // !WIDGETMANAGER