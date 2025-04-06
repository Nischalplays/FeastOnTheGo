#include <stdio.h>
#include <windows.h>
#include <gtk/gtk.h>
#include "main.h"
#include "products.h"
#include "itemManager.h"
#include "dataManager.h"
#include "widgetManager.h"
#include "structManager.h"

char *dataFilePath = "../src/data/FeastOnTheGo.db";
char *addItemTempImage;
int noOfProduct = 0;
char *addItemDefaultImage = "../src/img/addItemDefaultImage.jpg";
GtkWidget *defaultLoadBox;

void addItemToBox(GtkButton *button, gpointer user_data)
{
    item.imagePath = NULL;
    item.name = NULL;
    item.price = 0;
    item.discount = 0;
    item.destinationBox = user_data;

    const int current_window_width = 500;
    const int current_window_height = 500;

    GtkWidget *currentBox = GTK_WIDGET(user_data);

    GtkWidget *new_Item_Window;

    GtkWidget *grid;
    GtkWidget *inputGrid;

    GtkWidget *container;
    GtkWidget *image_box;
    GtkWidget *image_container_left;
    GtkWidget *image_container_right;
    GtkWidget *input_container;
    GtkWidget *addButtonContainer;
    GtkWidget *addButtonContainer1;

    GtkWidget *imageField;
    GtkWidget *nameEntry;
    GtkWidget *priceEntry;
    GtkWidget *discountEntry;
    GtkWidget *offerEntry;
    GtkWidget *categoryChooser;

    GtkWidget *firstText;
    GtkWidget *imageText;
    GtkWidget *nameText;
    GtkWidget *priceText;
    GtkWidget *discountText;
    GtkWidget *offerText;
    GtkWidget *categoryText;

    GtkWidget *defaultImage;
    GtkWidget *addButton;

    GtkWidget *combo;

    new_Item_Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(new_Item_Window), "Add Item");
    gtk_window_set_default_size(GTK_WINDOW(new_Item_Window), current_window_width, current_window_height);
    gtk_window_set_resizable(GTK_WINDOW(new_Item_Window), FALSE);
    g_signal_connect(new_Item_Window, "delete-event", G_CALLBACK(gtk_widget_destroy), NULL);

    item.addItemWindow = new_Item_Window;

    container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(new_Item_Window), container);

    firstText = gtk_label_new("New Item");
    gtk_widget_set_halign(GTK_WIDGET(firstText), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(firstText), -1, 50);
    gtk_box_pack_start(GTK_BOX(container), firstText, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(firstText), "newItem_text");

    image_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(image_box), current_window_width, 100);
    gtk_box_pack_start(GTK_BOX(container), image_box, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(image_box), "image_box");

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    image_container_left = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(image_box), image_container_left, FALSE, FALSE, 0);
    // gtk_widget_set_halign(GTK_WIDGET(image_container_left), GTK_ALIGN_START);
    gtk_widget_set_size_request(GTK_WIDGET(image_container_left), (int)((50.0 / 100.0) * current_window_width), 50);
    gtk_widget_set_name(GTK_WIDGET(image_container_left), "image_left_part");

    GtkWidget *emptyText = gtk_label_new(" ");
    GtkWidget *emptyText1 = gtk_label_new(" ");

    imageText = gtk_label_new("Image:");
    gtk_widget_set_name(GTK_WIDGET(imageText), "input_text");

    imageField = gtk_file_chooser_button_new("Open Image.", GTK_FILE_CHOOSER_ACTION_OPEN);

    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(GTK_FILE_FILTER(filter), "Image Files");
    gtk_file_filter_add_pattern(GTK_FILE_FILTER(filter), "*.jpg");
    gtk_file_filter_add_pattern(GTK_FILE_FILTER(filter), "*.jpeg");
    gtk_file_filter_add_pattern(GTK_FILE_FILTER(filter), "*.png");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(imageField), GTK_FILE_FILTER(filter));

    gtk_grid_attach(GTK_GRID(grid), emptyText, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), emptyText1, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), imageText, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), imageField, 1, 1, 1, 1);

    // g_signal_connect(imageField, "file-set", G_CALLBACK(on_file_set), &data);

    gtk_box_pack_start(GTK_BOX(image_container_left), grid, FALSE, FALSE, 0);

    image_container_right = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(image_box), image_container_right, FALSE, FALSE, 0);
    // gtk_widget_set_halign(GTK_WIDGET(image_container_left), GTK_ALIGN_START);
    gtk_widget_set_size_request(GTK_WIDGET(image_container_right), (int)((20.0 / 100.0) * current_window_width), -1);
    gtk_widget_set_name(GTK_WIDGET(image_container_right), "image_right_part");

    GdkPixbuf *addItemdefualtImageBuf = gdk_pixbuf_new_from_file_at_scale(addItemDefaultImage, 100, 100, FALSE, NULL);

    defaultImage = gtk_image_new_from_pixbuf(GDK_PIXBUF(addItemdefualtImageBuf));
    gtk_box_pack_start(GTK_BOX(image_container_right), defaultImage, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(defaultImage), "defaultImage");

    g_signal_connect(imageField, "file-set", G_CALLBACK(on_file_set), &item);
    item.imageEntry = imageField;
    item.defaultImageBox = defaultImage;

    input_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(container), input_container, TRUE, TRUE, 0);
    gtk_widget_set_name(GTK_WIDGET(input_container), "input_container");

    inputGrid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(inputGrid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(inputGrid), 10);
    gtk_widget_set_margin_top(GTK_WIDGET(inputGrid), 5);

    nameText = gtk_label_new("Name:");
    gtk_widget_set_name(GTK_WIDGET(nameText), "input_text");
    nameEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(nameEntry), "Food Name");
    gtk_widget_set_name(GTK_WIDGET(nameEntry), "entryBox");

    priceText = gtk_label_new("Price: ");
    gtk_widget_set_name(GTK_WIDGET(priceText), "input_text");
    priceEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(priceEntry), "Food Price");
    gtk_widget_set_name(GTK_WIDGET(priceEntry), "entryBox");

    discountText = gtk_label_new("Discount: ");
    gtk_widget_set_name(GTK_WIDGET(discountText), "input_text");
    discountEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(discountEntry), "Discount");
    gtk_widget_set_name(GTK_WIDGET(discountEntry), "entryBox");

    offerText = gtk_label_new("Offer:");
    gtk_widget_set_name(GTK_WIDGET(offerText), "input_text");
    offerEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(offerEntry), "offer");
    gtk_widget_set_name(GTK_WIDGET(offerEntry), "entryBox");

    categoryText = gtk_label_new("Category: ");
    gtk_widget_set_name(GTK_WIDGET(categoryText), "input_text");

    combo = gtk_combo_box_text_new();
    gtk_widget_set_name(GTK_WIDGET(combo), "entryBox");

    categoryOption(GTK_COMBO_BOX_TEXT(combo));

    gtk_grid_attach(GTK_GRID(inputGrid), nameText, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), nameEntry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), priceText, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), priceEntry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), discountText, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), discountEntry, 1, 2, 1, 1);
    // gtk_grid_attach(GTK_GRID(inputGrid), discountEntry, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), categoryText, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), combo, 1, 3, 1, 1);

    // gtk_grid_attach(GTK_GRID(inputGrid), addButtton, 1, 5, 2, 1);

    gtk_box_pack_start(GTK_BOX(input_container), inputGrid, FALSE, FALSE, 0);

    addButtonContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_end(GTK_BOX(input_container), addButtonContainer, FALSE, FALSE, 0);
    gtk_widget_set_margin_bottom(GTK_WIDGET(addButtonContainer), 15);
    // gtk_widget_set_name(GTK_WIDGET(addButtonContainer), "try");

    addButtonContainer1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_set_center_widget(GTK_BOX(addButtonContainer), GTK_WIDGET(addButtonContainer1));
    gtk_widget_set_size_request(GTK_WIDGET(addButtonContainer1), 200, 50);
    // gtk_widget_set_name(GTK_WIDGET(addButtonContainer1), "try1");

    item.nameField = nameEntry;
    item.priceField = priceEntry;
    item.discountField = discountEntry;
    item.comboBox = combo;

    addButton = gtk_button_new_with_label("Add Item");
    gtk_button_set_relief(GTK_BUTTON(addButton), GTK_RELIEF_NONE);
    gtk_box_pack_start(GTK_BOX(addButtonContainer1), addButton, TRUE, TRUE, 0);
    gtk_widget_set_name(GTK_WIDGET(addButton), "submitButton");

    g_signal_connect(addButton, "clicked", G_CALLBACK(on_submit), &item);

    gtk_widget_show_all(GTK_WIDGET(new_Item_Window));
}

void on_file_set(GtkFileChooserButton *filebutton, gpointer userdata)
{
    NewItem *data = (NewItem *)userdata;

    char *filepath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filebutton));
    if (!filepath)
    {
        g_print("No such path found.");
        return;
    }
    data->imagePath = strdup(filepath);
    // addItemTempImage = addItemDefaultImage;
    // addItemDefaultImage = data.imagePath;

    updata_image(data->imagePath, data);
    g_free(filepath);
}

GtkWidget *create_box(gpointer user_data)
{
    NewItem *itemdata = (NewItem *)user_data;

    deleteItem = malloc(sizeof(Delete));
    if(!deleteItem)
    {
        printf("failed allocating memory");
        return NULL;
    }
    const char *destinationBoxNam = gtk_widget_get_name(GTK_WIDGET(itemdata->destinationBox));

    

    GtkWidget *itemBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_size_request(GTK_WIDGET(itemBox), 300, 300);
    gtk_widget_set_name(GTK_WIDGET(itemBox), "newBox");
    gtk_widget_set_margin_start(GTK_WIDGET(itemBox), 10);

    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_CROSSFADE);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 300);
    
    GtkWidget *viewcontainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // gtk_box_pack_start(GTK_BOX(box), viewcontainer, TRUE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(viewcontainer), 300, 300);
    
    GtkWidget *imageContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(viewcontainer), imageContainer, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(imageContainer), 300, 200);
    gtk_widget_set_margin_top(GTK_WIDGET(imageContainer), 10);
    
    GtkWidget * imageHolder = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(imageContainer), imageHolder, TRUE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(imageHolder), 200, 200);
    gtk_widget_set_name(GTK_WIDGET(imageHolder), "newItemImage2");
    gtk_widget_set_halign(GTK_WIDGET(imageHolder), GTK_ALIGN_CENTER);
    
    GtkWidget *itemImage = createRoundedImage(itemdata->imagePath, 200, 200, 20);
    
    char *itemNameText = g_strdup_printf("Name: %s.", itemdata->name);
    GtkWidget *itemName = gtk_label_new(itemNameText);
    g_free(itemNameText);
    
    char *itemPriceText = g_strdup_printf("Price: %d.", itemdata->price);
    GtkWidget *itemPrice = gtk_label_new(itemPriceText);
    g_free(itemPriceText);
    
    gtk_box_pack_start(GTK_BOX(imageHolder), itemImage, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(viewcontainer), itemName, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(viewcontainer), itemPrice, FALSE, FALSE, 0);

    GtkWidget *optionContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    
    GtkWidget *emptyGrid = gtk_label_new("");
    gtk_widget_set_size_request(GTK_WIDGET(emptyGrid), 75, -1);
    GtkWidget *emptyGrid1 = gtk_label_new("");
    gtk_widget_set_size_request(GTK_WIDGET(emptyGrid1), 75, -1);
    GtkWidget *emptyGrid2 = gtk_label_new("");
    gtk_widget_set_size_request(GTK_WIDGET(emptyGrid2), 75, -1);
    GtkWidget *emptyGrid3 = gtk_label_new("");
    gtk_widget_set_size_request(GTK_WIDGET(emptyGrid3), 75, -1);
    
    // gtk_widget_set_name(GTK_WIDGET(emptyGrid), "try");
    // gtk_widget_set_name(GTK_WIDGET(emptyGrid1), "try");
    // gtk_widget_set_name(GTK_WIDGET(emptyGrid2), "try");
    // gtk_widget_set_name(GTK_WIDGET(emptyGrid3), "try");

    printf("Destination Box: %s |Image Path: %s |food name: %s | price: %d | dis: %d \n",destinationBoxNam, itemdata->imagePath, itemdata->name, itemdata->price, itemdata->discount);
    
    // deleteItem->id = product->id;
    deleteItem->box = itemBox; 
    deleteItem->products = product;
    deleteItem->filename = dataFilePath;
    deleteItem->boxContainer = itemdata->destinationBox;
    
    
    GtkWidget *addToCartButton = gtk_button_new_with_label("Add To Cart");
    gtk_widget_set_name(GTK_WIDGET(addToCartButton), "optionButton");
    GtkWidget *deleteItemButton = gtk_button_new_with_label("Delete");
    gtk_widget_set_name(GTK_WIDGET(deleteItemButton), "deleteButton");
    g_signal_connect(deleteItemButton, "clicked", G_CALLBACK(deleteItemWidget), deleteItem);
    
    gtk_grid_attach(GTK_GRID(grid), emptyGrid, 0, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), emptyGrid1, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), addToCartButton, 1, 1, 1, 1);
    gtk_widget_set_size_request(GTK_WIDGET(addToCartButton), 80, 5);
    gtk_grid_attach(GTK_GRID(grid), emptyGrid2, 0, 2, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), emptyGrid3, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), deleteItemButton, 1, 3, 1, 1);
    
    gtk_box_pack_start(GTK_BOX(optionContainer), grid, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(grid), 300, 300);
    gtk_widget_set_size_request(GTK_WIDGET(optionContainer), 300, 300);
    
    gtk_stack_add_named(GTK_STACK(stack), viewcontainer, "view"); 
    gtk_stack_add_named(GTK_STACK(stack), optionContainer, "option"); 
    
    GtkWidget * event_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(event_box), stack);
    gtk_widget_set_size_request(GTK_WIDGET(event_box), 300, 300);
    
    g_signal_connect(event_box, "enter-notify-event", G_CALLBACK(onHover), stack);
    g_signal_connect(event_box, "leave-notify-event", G_CALLBACK(onLeave), stack);
    
    gtk_box_pack_start(GTK_BOX(itemBox), event_box, TRUE, TRUE, 0);
    
    return itemBox;
}

void updata_image(char *newImagePath, gpointer user_data)
{
    NewItem *data = (NewItem *)user_data;

    GdkPixbuf *newImage = gdk_pixbuf_new_from_file_at_scale(newImagePath, 100, 100, FALSE, NULL);

    gtk_image_set_from_pixbuf(GTK_IMAGE(data->defaultImageBox), newImage);
    g_object_unref(newImage);
}

void on_submit(GtkButton *current_button, gpointer user_data)
{

    NewItem *data = (NewItem *)user_data;
    int success = 0;

    const char *lastNameEntry = gtk_entry_get_text(GTK_ENTRY(data->nameField));
    const char *lastPriceEntry = gtk_entry_get_text(GTK_ENTRY(data->priceField));
    const char *lastDiscountEntry = gtk_entry_get_text(GTK_ENTRY(data->discountField));

    if (lastNameEntry != NULL && strlen(lastNameEntry) != 0 && lastPriceEntry != NULL && strlen(lastPriceEntry) != 0 && data->imagePath != NULL)
    {

        data->name = strdup(gtk_entry_get_text(GTK_ENTRY(data->nameField)));
        data->price = atoi(gtk_entry_get_text(GTK_ENTRY(data->priceField)));
        if (lastDiscountEntry != NULL)
        {
            data->discount = atoi(gtk_entry_get_text(GTK_ENTRY(data->discountField)));
        }
        else
        {
            data->discount = 0;
        }

        if (emptyBox != NULL)
        {
            gtk_widget_destroy(GTK_WIDGET(emptyBox));
            emptyBox = NULL;
        }
        data->category = strdup(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->comboBox)));
        GtkWidget *vbox = create_box(data);
        gtk_box_pack_start(GTK_BOX(data->destinationBox), vbox, FALSE, FALSE, 0);

        gtk_widget_show_all(GTK_WIDGET(vbox));
        success = 1;
    }
    else
    {
        if (data->addItemWindow != NULL)
        {
            warningManager(data->addItemWindow, GTK_BUTTONS_OK, GTK_MESSAGE_ERROR,"Please fill all the details");
        }
    }
    printf("current category: %s\n", data->category);

    if (success)
    {

        // addProduct(NULL, data->imagePath, data->name, data->price, data->discount);
        // product[productCount].ImageFile = strdup(data->imagePath);
        // product[productCount].name = strdup(data->name);
        // product[productCount].price = data->price;
        // product[productCount].discount = data->discount;
        saveMenuData(data, dataFilePath);

        // data->imagePath = NULL;
        // gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(data->imageEntry), "");
        // data->name = NULL;
        // data->price = 0;
        // data->discount = 0;
        // gtk_entry_set_text(GTK_ENTRY(data->nameField), "");
        // gtk_entry_set_text(GTK_ENTRY(data->priceField), "");
        // gtk_entry_set_text(GTK_ENTRY(data->discountField), "");
    }
}

GtkWidget *load_box(GtkWidget *boxToLoad, gpointer user_data)
{
    Products *product = (Products *)user_data;
    Delete *deleteWidget = malloc(sizeof(Delete));

    GtkWidget *itemBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_size_request(GTK_WIDGET(itemBox), 300, 300);
    gtk_widget_set_name(GTK_WIDGET(itemBox), "newBox");
    gtk_widget_set_margin_start(GTK_WIDGET(itemBox), 10);

    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_CROSSFADE);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 300);
    
    GtkWidget *viewcontainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // gtk_box_pack_start(GTK_BOX(box), viewcontainer, TRUE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(viewcontainer), 300, 300);
    
    GtkWidget *imageContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(viewcontainer), imageContainer, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(imageContainer), 300, 200);
    gtk_widget_set_margin_top(GTK_WIDGET(imageContainer), 10);
    
    GtkWidget * imageHolder = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(imageContainer), imageHolder, TRUE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(imageHolder), 200, 200);
    gtk_widget_set_name(GTK_WIDGET(imageHolder), "newItemImage2");
    gtk_widget_set_halign(GTK_WIDGET(imageHolder), GTK_ALIGN_CENTER);
    
    GtkWidget *itemImage = createRoundedImage(product->ImageFile, 200, 200, 20);
    
    char *itemNameText = g_strdup_printf("Name: %s.", product->name);
    GtkWidget *itemName = gtk_label_new(itemNameText);
    g_free(itemNameText);
    
    char *itemPriceText = g_strdup_printf("Price: %d.", product->price);
    GtkWidget *itemPrice = gtk_label_new(itemPriceText);
    g_free(itemPriceText);
    
    gtk_box_pack_start(GTK_BOX(imageHolder), itemImage, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(viewcontainer), itemName, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(viewcontainer), itemPrice, FALSE, FALSE, 0);

    GtkWidget *optionContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    
    GtkWidget *emptyGrid = gtk_label_new("");
    gtk_widget_set_size_request(GTK_WIDGET(emptyGrid), 75, -1);
    GtkWidget *emptyGrid1 = gtk_label_new("");
    gtk_widget_set_size_request(GTK_WIDGET(emptyGrid1), 75, -1);
    GtkWidget *emptyGrid2 = gtk_label_new("");
    gtk_widget_set_size_request(GTK_WIDGET(emptyGrid2), 75, -1);
    GtkWidget *emptyGrid3 = gtk_label_new("");
    gtk_widget_set_size_request(GTK_WIDGET(emptyGrid3), 75, -1);
    
    // gtk_widget_set_name(GTK_WIDGET(emptyGrid), "try");
    // gtk_widget_set_name(GTK_WIDGET(emptyGrid1), "try");
    // gtk_widget_set_name(GTK_WIDGET(emptyGrid2), "try");
    // gtk_widget_set_name(GTK_WIDGET(emptyGrid3), "try");

    deleteWidget->id = product->id;
    deleteWidget->box = itemBox; 
    deleteWidget->products = product;
    deleteWidget->filename = dataFilePath;
    deleteWidget->boxContainer = boxToLoad;

    
    GtkWidget *addToCartButton = gtk_button_new_with_label("Add To Cart");
    gtk_widget_set_name(GTK_WIDGET(addToCartButton), "optionButton");
    GtkWidget *deleteItemButton = gtk_button_new_with_label("Delete");
    gtk_widget_set_name(GTK_WIDGET(deleteItemButton), "deleteButton");
    g_signal_connect(deleteItemButton, "clicked", G_CALLBACK(deleteItemWidget), deleteWidget);
    
    gtk_grid_attach(GTK_GRID(grid), emptyGrid, 0, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), emptyGrid1, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), addToCartButton, 1, 1, 1, 1);
    gtk_widget_set_size_request(GTK_WIDGET(addToCartButton), 80, 5);
    gtk_grid_attach(GTK_GRID(grid), emptyGrid2, 0, 2, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), emptyGrid3, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), deleteItemButton, 1, 3, 1, 1);
    
    gtk_box_pack_start(GTK_BOX(optionContainer), grid, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(grid), 300, 300);
    gtk_widget_set_size_request(GTK_WIDGET(optionContainer), 300, 300);

    gtk_stack_add_named(GTK_STACK(stack), viewcontainer, "view"); 
    gtk_stack_add_named(GTK_STACK(stack), optionContainer, "option"); 

    GtkWidget * event_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(event_box), stack);
    gtk_widget_set_size_request(GTK_WIDGET(event_box), 300, 300);

    g_signal_connect(event_box, "enter-notify-event", G_CALLBACK(onHover), stack);
    g_signal_connect(event_box, "leave-notify-event", G_CALLBACK(onLeave), stack);

    gtk_box_pack_start(GTK_BOX(itemBox), event_box, TRUE, TRUE, 0);
    return itemBox;
}

void loadItemBox(Products *product)
{
    int i;
    for (i = 0; i < productCount; i++)
    {
        GtkWidget *boxToLoad = searchCategoryContainer(product[i].category);
        GtkWidget *vbox = load_box(boxToLoad, &product[i]);
        if(boxToLoad)
        {
            gtk_box_pack_start(GTK_BOX(boxToLoad), vbox, FALSE, FALSE, 0);
        }
    }
}