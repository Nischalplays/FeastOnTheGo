#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *imagePath;
    char *name;
    int price;
    GtkWidget *nameField;
    GtkWidget *priceField;
    GtkWidget *destinationBox;
} NewItem;

const int width = 1200;
const int height = 800;

static void on_submit(GtkButton current_button, gpointer user_data)
{
    NewItem *data = (NewItem *)user_data;

    
}
GtkWidget create_box(char* box_name, gpointer userdata)
{
    GtkWidget box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget boxName = gtk_label_new(box_name);

    return box;
}

static void on_checkbox_toggle(GtkToggleButton checkButton, gpointer user)
{
    if(gtk_toggle_action_get_active(checkButton))
    {
        g_print("")
    }
}

static void on_file_set(GtkFileChooserButton *filebutton, gpointer userdata) {
    NewItem *data = (NewItem *)userdata;

    char *filepath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filebutton));
    if (!filepath)
    {
        g_print("No such path found.");
        return;
    }
    data->imagePath = strdup(filepath);

    g_free(filepath);
}


void addItemToBox(GtkButton *button, gpointer user_data)
{
    NewItem *data = g_malloc(sizeof(NewItem));
    data->imagePath = NULL;
    data->name = NULL;
    data->price = 0;

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

    GtkWidget *firstText;
    GtkWidget *imageText;
    GtkWidget *nameText;
    GtkWidget *priceText;
    GtkWidget *discountText;
    GtkWidget *offerText;

    GtkWidget *defaultImage;
    GtkWidget *addButton;

    GtkWidget *trendingCheckbox;
    GtkWidget *offerCheckbox;

    new_Item_Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(new_Item_Window), "Add Item");
    gtk_window_set_default_size(GTK_WINDOW(new_Item_Window), current_window_width, current_window_height);
    gtk_window_set_resizable(GTK_WINDOW(new_Item_Window), FALSE);
    g_signal_connect(new_Item_Window, "delete-event", G_CALLBACK(gtk_widget_destroy), NULL);

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
    g_signal_connect(imageField, "file-set", G_CALLBACK(on_file_set), data);

    gtk_box_pack_start(GTK_BOX(image_container_left), grid, FALSE, FALSE, 0);

    image_container_right = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(image_box), image_container_right, FALSE, FALSE, 0);
    // gtk_widget_set_halign(GTK_WIDGET(image_container_left), GTK_ALIGN_START);
    gtk_widget_set_size_request(GTK_WIDGET(image_container_right), (int)((20.0 / 100.0) * current_window_width), -1);
    gtk_widget_set_name(GTK_WIDGET(image_container_right), "image_right_part");

    GdkPixbuf *addItemdefualtImageBuf = gdk_pixbuf_new_from_file_at_scale("img/addItemDefaultImage.jpg", 100, 100, FALSE, NULL);

    defaultImage = gtk_image_new_from_pixbuf(GDK_PIXBUF(addItemdefualtImageBuf));
    gtk_box_pack_start(GTK_BOX(image_container_right), defaultImage, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(defaultImage), "defaultImage");

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

    trendingCheckbox = gtk_check_button_new_with_label("Trending");
    gtk_widget_set_name(GTK_WIDGET(trendingCheckbox), "checkBox");
    g_signal_connect(trendingCheckbox, "toggle", G_CALLBACK(on_checkbox_toggle), NULL);

    offerCheckbox = gtk_check_button_new_with_label("Offer");
    gtk_widget_set_name(GTK_WIDGET(offerCheckbox), "checkBox");

    gtk_grid_attach(GTK_GRID(inputGrid), nameText, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), nameEntry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), priceText, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), priceEntry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), discountText, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), discountEntry, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), offerText, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), offerEntry, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), trendingCheckbox, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(inputGrid), offerCheckbox, 1, 4, 1, 1);
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

    data->nameField = nameEntry;
    data->priceField = priceEntry;
    
    addButton = gtk_button_new_with_label("Add Item");
    gtk_button_set_relief(GTK_BUTTON(addButton), GTK_RELIEF_NONE);
    gtk_box_pack_start(GTK_BOX(addButtonContainer1), addButton, TRUE, TRUE, 0);
    gtk_widget_set_name(GTK_WIDGET(addButton), "hello");
    
    g_signal_connect(addButton, "clicked", G_CALLBACK(on_entry_activate), data);

    gtk_widget_show_all(GTK_WIDGET(new_Item_Window));
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *scrolledWindow;

    // ---------{[Containers]}---------
    GtkWidget *topBar;
    GtkWidget *mainContainer;
    GtkWidget *topBar_left_side;
    GtkWidget *topBar_right_side;
    GtkWidget *topBar_middle_side;
    GtkWidget *contentBox;
    GtkWidget *TrendingAddContainer;
    GtkWidget *TrendingContainer;
    GtkWidget *TrendingBox;
    GtkWidget *offereAddContainer;
    GtkWidget *offerContainer;
    GtkWidget *offerBox;

    // ---------{[Buttons]}---------
    GtkWidget *logo;
    GtkWidget *homeButton;
    GtkWidget *productsButton;
    GtkWidget *aboutButton;
    GtkWidget *contactUsButton;
    GtkWidget *loginSignUpButton;
    GtkWidget *cartButton;
    GtkWidget *addItem;

    GtkWidget *FrontImage;
    GtkWidget *viewport;
    GtkWidget *cartLogo;

    // ---------{[TEXTS]}---------
    GtkWidget *greetingText;
    GtkWidget *trendingText;
    GtkWidget *offerText;

    // ---------{[window]}---------
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Fast Foods");
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    // ---------{[main Container Box]}---------
    mainContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), mainContainer);

    // ---------{[Nav Bar Box]}---------
    topBar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_widget_set_size_request(topBar, -1, 80);
    gtk_box_pack_start(GTK_BOX(mainContainer), topBar, FALSE, FALSE, 0);

    gtk_widget_set_name(topBar, "nav_bar");

    topBar_left_side = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(topBar), topBar_left_side, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(topBar_left_side), (int)((10.0 / 100.0) * width), -1);
    // gtk_widget_set_name(topBar_left_side, "left_side");

    GdkPixbuf *logoBuf = gdk_pixbuf_new_from_file_at_size("img/logo_1.png", 70, 70, NULL);
    logo = gtk_image_new_from_pixbuf(GDK_PIXBUF(logoBuf));
    g_object_unref(logoBuf);
    gtk_widget_set_name(GTK_WIDGET(logo), "logo");

    gtk_box_set_center_widget(GTK_BOX(topBar_left_side), logo);

    topBar_middle_side = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_set_center_widget(GTK_BOX(topBar), GTK_WIDGET(topBar_middle_side));
    gtk_widget_set_name(GTK_WIDGET(topBar_middle_side), "middle_box");
    gtk_widget_set_size_request(GTK_WIDGET(topBar_middle_side), (int)((60.0 / 100.0) * width), -1);

    homeButton = gtk_button_new_with_label("Home");
    gtk_box_pack_start(GTK_BOX(topBar_middle_side), homeButton, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(homeButton), 80, 40);
    gtk_button_set_relief(GTK_BUTTON(homeButton), GTK_RELIEF_NONE);

    productsButton = gtk_button_new_with_label("Products");
    gtk_box_pack_start(GTK_BOX(topBar_middle_side), productsButton, FALSE, FALSE, 10);
    gtk_button_set_relief(GTK_BUTTON(productsButton), GTK_RELIEF_NONE);

    aboutButton = gtk_button_new_with_label("About Us");
    gtk_box_pack_start(GTK_BOX(topBar_middle_side), aboutButton, FALSE, FALSE, 10);
    gtk_button_set_relief(GTK_BUTTON(aboutButton), GTK_RELIEF_NONE);

    contactUsButton = gtk_button_new_with_label("Contact us");
    gtk_box_pack_start(GTK_BOX(topBar_middle_side), contactUsButton, FALSE, FALSE, 10);
    gtk_button_set_relief(GTK_BUTTON(contactUsButton), GTK_RELIEF_NONE);

    gtk_widget_set_name(GTK_WIDGET(homeButton), "nav_button");
    gtk_widget_set_name(GTK_WIDGET(productsButton), "nav_button");
    gtk_widget_set_name(GTK_WIDGET(aboutButton), "nav_button");
    gtk_widget_set_name(GTK_WIDGET(contactUsButton), "nav_button");

    topBar_right_side = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_end(GTK_BOX(topBar), topBar_right_side, FALSE, FALSE, 10);
    gtk_widget_set_size_request(GTK_WIDGET(topBar_right_side), (int)((15.0 / 100.0) * width), -1);
    gtk_widget_set_name(GTK_WIDGET(topBar_right_side), "right_side");

    loginSignUpButton = gtk_button_new_with_label("Login/Signup");
    gtk_button_set_relief(GTK_BUTTON(loginSignUpButton), GTK_RELIEF_NONE);
    gtk_box_pack_start(GTK_BOX(topBar_right_side), GTK_WIDGET(loginSignUpButton), FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(loginSignUpButton), "loginButton");
    ;
    cartButton = gtk_button_new();
    gtk_button_set_relief(GTK_BUTTON(cartButton), GTK_RELIEF_NONE);

    GdkPixbuf *cartBuf = gdk_pixbuf_new_from_file_at_scale("img/cart.png", 35, 40, TRUE, NULL);

    cartLogo = gtk_image_new_from_pixbuf(cartBuf);
    g_object_unref(cartBuf);
    gtk_button_set_image(GTK_BUTTON(cartButton), GTK_WIDGET(cartLogo));
    gtk_box_pack_end(GTK_BOX(topBar_right_side), cartButton, FALSE, FALSE, 0);

    //----------{[End of nav bar and start of main content]}------------

    scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_name(GTK_WIDGET(scrolledWindow), "scrolledWindow");
    gtk_box_pack_start(GTK_BOX(mainContainer), GTK_WIDGET(scrolledWindow), TRUE, TRUE, 0);

    contentBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(scrolledWindow), contentBox);
    gtk_widget_set_name(GTK_WIDGET(contentBox), "contentBox");

    GdkPixbuf *pixBuf = gdk_pixbuf_new_from_file_at_scale("img/MainPicture_1.jpg", width, height - 80, FALSE, NULL);
    FrontImage = gtk_image_new_from_pixbuf(GDK_PIXBUF(pixBuf));
    g_object_unref(pixBuf);

    gtk_box_pack_start(GTK_BOX(contentBox), GTK_WIDGET(FrontImage), FALSE, FALSE, 0);

    TrendingAddContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(contentBox), TrendingAddContainer, FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(TrendingAddContainer), "addContainer");

    trendingText = gtk_label_new("Trending");
    gtk_widget_set_halign(GTK_WIDGET(trendingText), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(TrendingAddContainer), trendingText, FALSE, FALSE, 5);
    gtk_widget_set_name(GTK_WIDGET(trendingText), "FeaturedText");

    addItem = gtk_button_new_from_icon_name("tab-new", GTK_ICON_SIZE_BUTTON);
    gtk_widget_set_size_request(GTK_WIDGET(addItem), 20, 20);
    gtk_box_pack_start(GTK_BOX(TrendingAddContainer), addItem, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(addItem), GTK_ALIGN_START);

    TrendingContainer = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(TrendingContainer), GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);
    gtk_box_pack_start(GTK_BOX(contentBox), TrendingContainer, FALSE, TRUE, 0);
    gtk_widget_set_name(GTK_WIDGET(TrendingContainer), "featuredContainer");

    TrendingBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(TrendingContainer), TrendingBox);
    gtk_widget_set_size_request(GTK_WIDGET(TrendingBox), width, 300);
    gtk_widget_set_name(GTK_WIDGET(TrendingBox), "featuredBox");

    // g_signal_connect(addItem, "clicked", G_CALLBACK(addItemToBox), TrendingBox);
    GtkWidget new_box = g_signal_connect(addItem, "clicked", G_CALLBACK(create_box), NULL);
    gtk_box_pack_start(GTK_BOX(trendingText), new_box, FALSE, FALSE, 5);

    offerText = gtk_label_new("Offers");
    gtk_widget_set_halign(GTK_WIDGET(offerText), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(contentBox), offerText, FALSE, FALSE, 5);
    gtk_widget_set_name(GTK_WIDGET(offerText), "FeaturedText");

    offerContainer = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(offerContainer), GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);
    gtk_box_pack_start(GTK_BOX(contentBox), offerContainer, FALSE, TRUE, 0);
    gtk_widget_set_name(GTK_WIDGET(offerContainer), "featuredContainer");

    offerBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(offerContainer), offerBox);
    gtk_widget_set_size_request(GTK_WIDGET(offerBox), width, 300);
    gtk_widget_set_name(GTK_WIDGET(offerBox), "featuredBox");

    GtkCssProvider *css_provider = gtk_css_provider_new();
    GError *error = NULL;
    gtk_css_provider_load_from_path(css_provider, "style.css", &error);
    if (error)
    {
        g_printerr("error loading css file: %s\n", error->message);
        g_error_free(error);
    }

    GtkStyleContext *context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(css_provider);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("test.gtkproject", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
}