#include <stdio.h>
#include <gtk/gtk.h>
#include "widgetManager.h"
#include "itemManager.h"
#include "dataManager.h"
#include "main.h"
#include "products.h"
#include "structManager.h"

GtkWidget *createBox_with_text(int boxWidth, int boxHeight, const char *text, GtkOrientation orientation, const char *widgetName)
{
    GtkWidget *box;
    GtkWidget *label;

    box = gtk_box_new(orientation, 0);
    label = gtk_label_new(text);

    // gtk_label_set_xalign(GTK_LABEL(label), 0.0);  // Align left (0.0 = left, 1.0 = right, 0.5 = center)
    gtk_widget_set_halign(label, GTK_ALIGN_START); // Align horizontally within the box
    gtk_widget_set_valign(label, GTK_ALIGN_CENTER);

    gtk_box_pack_start(GTK_BOX(box), label, TRUE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(box), boxWidth, boxHeight);
    if (widgetName != NULL)
    {
        gtk_widget_set_name(GTK_WIDGET(box), widgetName);
    }

    return box;
}

GtkWidget *createButton_with_text(int boxWidth, int boxHeight, const char *text)
{
    GtkWidget *button;
    button = gtk_button_new_with_label(text);
    gtk_widget_set_size_request(GTK_WIDGET(button), boxWidth, boxHeight);

    return button;
}

GtkWidget *createCategoryWindow()
{
    GtkWidget *newWindow;
    GtkWidget *grid;
    GtkWidget *categoryText;
    GtkWidget *categoryEntry;
    GtkWidget *addButton;

    newWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(newWindow), "New Category");
    gtk_window_set_default_size(GTK_WINDOW(newWindow), 400, 300);
    gtk_window_set_resizable(GTK_WINDOW(newWindow), FALSE);

    g_signal_connect(newWindow, "delete-event", G_CALLBACK(gtk_widget_destroy), NULL);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    categoryText = gtk_label_new("New Category");
    gtk_widget_set_name(GTK_WIDGET(categoryText), "FeaturedText");

    categoryEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(categoryEntry), "New Category name..");
    gtk_widget_set_name(GTK_WIDGET(categoryEntry), "entryBox");

    addButton = gtk_button_new_with_label("Add");
    gtk_widget_set_name(GTK_WIDGET(addButton), "submitButton");

    gtk_grid_attach(GTK_GRID(grid), categoryText, 1, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), categoryEntry, 0, 1, 4, 1);
    gtk_grid_attach(GTK_GRID(grid), addButton, 1, 2, 2, 1);

    g_signal_connect(addButton, "clicked", G_CALLBACK(onAddCategory), categoryEntry);

    gtk_container_add(GTK_CONTAINER(newWindow), grid);

    return newWindow;
}

int warningManager(GtkWidget *destinationWindow, GtkButtonsType buttonType, GtkMessageType messageType ,const char *warningText)
{
    GtkWidget *warning = gtk_message_dialog_new(GTK_WINDOW(destinationWindow),
                                                GTK_DIALOG_MODAL,
                                                messageType,
                                                buttonType,
                                                warningText);
    gtk_widget_show_all(warning);
    int response = gtk_dialog_run(GTK_DIALOG(warning));
    gtk_widget_destroy(warning);
    if (buttonType == GTK_BUTTONS_YES_NO)
    {
        return (response == GTK_RESPONSE_YES) ? 1 : 0;
    }
    else if( buttonType == GTK_BUTTONS_OK || buttonType == GTK_BUTTONS_CANCEL)
    {
        return (response == GTK_RESPONSE_OK) ? 1 : 0;
    }
    else if (buttonType == GTK_BUTTONS_CLOSE || buttonType == GTK_BUTTONS_NONE){
        return 0;
    }

    return 0;
}

GdkPixbuf *createRoundedPixbuf(GdkPixbuf *src, int radius)
{
    int width = gdk_pixbuf_get_width(src);
    int height = gdk_pixbuf_get_height(src);

    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create(surface);

    // Clear the surface with full transparency
    cairo_set_source_rgba(cr, 0, 0, 0, 0);
    cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
    cairo_paint(cr);

    // Draw the rounded rectangle mask
    cairo_new_path(cr);
    cairo_arc(cr, radius, radius, radius, G_PI, G_PI * 3 / 2);
    cairo_arc(cr, width - radius, radius, radius, G_PI * 3 / 2, 0);
    cairo_arc(cr, width - radius, height - radius, radius, 0, G_PI / 2);
    cairo_arc(cr, radius, height - radius, radius, G_PI / 2, G_PI);
    cairo_close_path(cr);
    cairo_clip(cr);

    // Draw the original image inside the clipped region
    gdk_cairo_set_source_pixbuf(cr, src, 0, 0);
    cairo_paint(cr);

    // Convert Cairo surface back to GdkPixbuf
    GdkPixbuf *roundedPixbuf = gdk_pixbuf_get_from_surface(surface, 0, 0, width, height);

    // Cleanup
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    return roundedPixbuf;
}

GtkWidget *createRoundedImage(const char *filepath, int width, int height, int radius)
{
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(filepath, width, height, FALSE, NULL);

    if(!pixbuf) return NULL;

    GdkPixbuf *rounded = createRoundedPixbuf(pixbuf, radius);
    GtkWidget *image = gtk_image_new_from_pixbuf(rounded);

    g_object_unref(pixbuf);
    g_object_unref(rounded);

    return image;
}

gboolean onHover (GtkWidget *widget, GdkEventCrossing *event, gpointer user_data)
{
    GtkStack *stack = GTK_STACK(user_data);
    gtk_stack_set_visible_child_name(stack, "option");
    return FALSE;
}

gboolean onLeave (GtkWidget *widget, GdkEventCrossing *event, gpointer user_data)
{
    GtkStack *stack = GTK_STACK(user_data);
    gtk_stack_set_visible_child_name(stack, "view");
    return FALSE;
}

void deleteItemWidget(GtkWidget *widget, gpointer userdata)
{
    Delete *deleteingItem = (Delete *)userdata;
    GtkWidget *itemBox = gtk_widget_get_parent(GTK_WIDGET(deleteingItem->box));
    const char *widgetName = gtk_widget_get_name(GTK_WIDGET(deleteingItem->box));
    
    if(itemBox != NULL)
    {
        int response = warningManager(mainWindow, GTK_BUTTONS_YES_NO, GTK_MESSAGE_QUESTION, "Do you want to delete the widget? ");
        if(response)
        {
            gtk_widget_destroy(GTK_WIDGET(deleteingItem->box));
            // deleteMenuData(deleteItem->filename, deleteItem->id);
            if(isTableEmpty(deleteingItem->filename, "menu"))
            {
                g_print("creating new empty box");
                emptyBox = createBox_with_text(300, -1, "No Items Available Currently.", GTK_ORIENTATION_VERTICAL, "newBox"); 
                if(deleteingItem->boxContainer != NULL)
                {
                    gtk_box_pack_start(GTK_BOX(deleteingItem->boxContainer), emptyBox, FALSE, FALSE, 0);
                    gtk_widget_set_margin_start(GTK_WIDGET(emptyBox), 10);
                    gtk_widget_show_all(GTK_WIDGET(emptyBox));
                }
            }
            free(deleteingItem);
        }
    }
}

GtkWidget *createCategoryBox(GtkWidget *destToCreate, WidgetType type, const char *CategoryName)
{
    const char *categoryNameText =  NULL;
    
    printf("works until here");
    if(type == SAVE)
    {
        categoryNameText = strdup(category.name);
    }
    else if(type == LOAD)
    {
        categoryNameText = strdup(CategoryName);
    }


    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(container), -1, 350);
    gtk_widget_set_name(container, "categoryBox");
    
    GtkWidget * topBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(container), topBox, TRUE, FALSE, 0);
    gtk_widget_set_size_request(topBox, -1, 50);
    gtk_widget_set_name(topBox, "try");

    GtkWidget *categoryName = gtk_label_new(categoryNameText);
    gtk_box_pack_start(GTK_BOX(topBox), categoryName, FALSE, FALSE, 0);
    gtk_widget_set_name(categoryName, "FeaturedText");

    GtkWidget *CategoryContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(container), CategoryContainer, FALSE, FALSE, 0);
    gtk_widget_set_size_request(CategoryContainer, -1, 300);
    gtk_widget_set_name(CategoryContainer, "boxWithBorder");


    return container;
}

void onAddCategory(GtkWidget *button, gpointer user_data)
{
    GtkWidget *categoryEntry = GTK_WIDGET(user_data);

    const char * entryData = gtk_entry_get_text(GTK_ENTRY(categoryEntry));

    if(entryData != NULL && strlen(entryData) != 0)
    {
        const char *warningText = g_strdup_printf("Are you sure you wanna add %s?", entryData);
        if(warningManager(mainWindow, GTK_BUTTONS_YES_NO, GTK_MESSAGE_WARNING, warningText) == 1)
        {
            category.name = strdup(entryData);
            saveCategoryData(&category, dataFilePath);
            // insertIntoCategoryContainer()
        }
    }
}

GtkWidget *createCategoryButton(GtkWidget *destinationToCreate, gpointer user_data)
{
    AllCategory *categoryToLoad = (AllCategory *)user_data;

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(box, -1, 40);

    GtkWidget *button = gtk_button_new_with_label((const char *)categoryToLoad->name);
    gtk_widget_set_name(button, "categoryButton");
    gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);

    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);

    return box;
}