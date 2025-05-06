#include <gtk/gtk.h>
#include <stdio.h>
#include "main.h"
#include "products.h"
#include "widgetManager.h"
#include "dataManager.h"
#include "itemManager.h"

GtkWidget *categoryTopContainer;
int categoryEmpty = TRUE;
GtkWidget *categoryContent;

void on_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget *newCategoryWindow;

    newCategoryWindow = createCategoryWindow();
    gtk_widget_show_all(GTK_WIDGET(newCategoryWindow));
}

void load_category(gpointer boxToLoad)
{
    for (int i = 0; i < categoryCount; i++)
    {
        GtkWidget *newBox = createCategoryBox(GTK_WIDGET(boxToLoad), ACTION_LOAD, categorys[i].name, i);
        gtk_box_pack_start(GTK_BOX(boxToLoad), newBox, FALSE, FALSE, 0);
    }
}

GtkWidget *createProductPage()
{
    if(isTableEmpty(dataFilePath, "category") == 0)
    {
        loadCategoryData(dataFilePath);
        categoryEmpty = FALSE;
    }

    GtkWidget *productPageContainer;
    GtkWidget *categoryContainer;
    
    GtkWidget *categoryBottomContainer;
    GtkWidget *foodItemContainer;
    GtkWidget *categoryBox;
    GtkWidget *foodItemBox;
    GtkWidget *addButtonContainer;
    GtkWidget *addCategory;
    
    productPageContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(productPageContainer), -1, WIN_HEIGHT - 90);
    // gtk_widget_set_name(GTK_WIDGET(productPageContainer), "ProductPage");
    
    categoryContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(categoryContainer), 400, WIN_HEIGHT - 80);
    gtk_widget_set_name(GTK_WIDGET(categoryContainer), "productContainer");
    gtk_box_pack_start(GTK_BOX(productPageContainer), categoryContainer, FALSE, FALSE, 0);
    
    categoryTopContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(categoryTopContainer), 300, 50);
    gtk_box_pack_start(GTK_BOX(categoryContainer), categoryTopContainer, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(categoryTopContainer), "categoryContainerTop");

    addCategory = gtk_button_new_with_label("Add Category");
    gtk_box_pack_start(GTK_BOX(categoryTopContainer), addCategory, TRUE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(addCategory), "addCategory");

    g_signal_connect(addCategory, "clicked", G_CALLBACK(on_clicked), categoryTopContainer);
    
    categoryBottomContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(categoryContainer), categoryBottomContainer, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(categoryBottomContainer), -1, WIN_HEIGHT - 80 - 50);
    // gtk_widget_set_margin_top(GTK_WIDGET(categoryBottomContainer), 10);
    gtk_widget_set_name(GTK_WIDGET(categoryBottomContainer), "categoryContainerBottom");
    
    categoryBox = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(categoryBox), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(categoryBottomContainer), categoryBox, TRUE, TRUE, 0);

    categoryContent = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(categoryBox), categoryContent);

    if(!categoryEmpty)
    {
        for(int i = 0; i < categoryCount; i++)
        {
            char *name = strdup(categorys[i].name);
            GtkWidget *vbox = createCategoryButton(categoryBox, name);
            gtk_box_pack_start(GTK_BOX(categoryContent), vbox, FALSE, FALSE, 0);
        }
    }
    
    foodItemContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(foodItemContainer), 790, WIN_HEIGHT - 80);

    GtkWidget *AddProductButton = createButton_with_text(-1, 50, "Add Product");
    gtk_box_pack_start(GTK_BOX(foodItemContainer), AddProductButton, FALSE, FALSE, 0);
    gtk_widget_set_name(AddProductButton, "addCategory");
    g_signal_connect(AddProductButton, "clicked", G_CALLBACK(createItemBox), NULL);

    foodItemBox = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(foodItemBox), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(foodItemContainer), foodItemBox, TRUE, TRUE, 0);
    gtk_widget_set_name(GTK_WIDGET(foodItemBox), "productContainer");

    GtkWidget *contentBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(foodItemBox), contentBox);

    if(!categoryEmpty)
    {
        load_category(contentBox);
    }

    if(!dataBaseEmpty)
    {
        loadItemBox(product);
    }

    gtk_box_pack_end(GTK_BOX(productPageContainer), foodItemContainer, FALSE, FALSE, 0);

    return productPageContainer;
}