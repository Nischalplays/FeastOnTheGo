#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "products.h"
#include "itemManager.h"
#include "dataManager.h"
#include "widgetManager.h"
#include "structManager.h"

// #define TRUE 0
// #define FALSE

int WIN_WIDTH = 1200;
int WIN_HEIGHT = 800;
int dataBaseEmpty = FALSE;
GtkWidget *emptyBox = NULL;

GtkWidget *mainWindow;
GtkWidget *homeButton;
GtkWidget *productsButton;

void update_button_state(GtkWidget *active_button)
{
    gtk_widget_set_sensitive(homeButton, TRUE);
    gtk_widget_set_sensitive(productsButton, TRUE);

    gtk_widget_set_sensitive(active_button, FALSE);
}

void switch_stack_page(GtkWidget *widget, gpointer user_data)
{
    GtkStack *stack = GTK_STACK(user_data);
    const char *page_name = gtk_widget_get_name(widget);

    if(gtk_stack_get_child_by_name(stack, page_name))
    {
        gtk_stack_set_visible_child_name(stack, page_name);
        update_button_state(widget);
    }
    else
    {
        g_print("Error: Stack child '%s' not found.\n", page_name);
    }
}

static void activate(GtkApplication *app, gpointer user_data)
{

    if(isTableEmpty(dataFilePath, "menu") == 1)
    {
        printf("Table is empty.\n");
        printf("No Loading Required.\n");
        dataBaseEmpty = TRUE;
    }
    else if(isTableEmpty(dataFilePath, "menu") == 0)
    {
        printf("Found Menu data.\n");
        printf("Loading data.\n");
        loadMenuData(dataFilePath);
    }
    else if(isTableEmpty(dataFilePath, "menu") == -1)
    {
        printf("Error occured.\n");
        dataBaseEmpty = TRUE;
    }

    // printMenuData(product, productCount);

    GtkWidget *scrolledWindow;

    // ---------{[Containers]}---------
    GtkWidget *topBar;
    GtkWidget *mainContainer;
    GtkWidget *pageContainer;
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
    // GtkWidget *homeButton;
    // GtkWidget *productsButton;
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

    // ---------{[EXTRAS]}---------
    GtkWidget *home;
    defaultLoadBox = TrendingBox;
    GtkWidget *stack;

    // ---------{[window]}---------
    mainWindow = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "Feast On The Go");
    gtk_window_set_default_icon_from_file("../src/img/winLogo.png", NULL);
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), WIN_WIDTH, WIN_HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(mainWindow), FALSE);

    // ---------{[main Container Box]}---------
    mainContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(mainWindow), mainContainer);
    gtk_widget_set_size_request(GTK_WIDGET(mainContainer), WIN_WIDTH, WIN_HEIGHT);

    // ---------{[Nav Bar Box]}---------
    topBar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_widget_set_size_request(topBar, -1, 80);
    gtk_box_pack_start(GTK_BOX(mainContainer), topBar, FALSE, FALSE, 0);

    gtk_widget_set_name(topBar, "nav_bar");

    topBar_left_side = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(topBar), topBar_left_side, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(topBar_left_side), (int)((10.0 / 100.0) * WIN_WIDTH), -1);
    // gtk_widget_set_name(topBar_left_side, "left_side");

    GdkPixbuf *logoBuf = gdk_pixbuf_new_from_file_at_size("../src/img/logo_1.png", 70, 70, NULL);
    logo = gtk_image_new_from_pixbuf(GDK_PIXBUF(logoBuf));
    g_object_unref(logoBuf);
    gtk_widget_set_name(GTK_WIDGET(logo), "logo");

    gtk_box_set_center_widget(GTK_BOX(topBar_left_side), logo);

    topBar_middle_side = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_set_center_widget(GTK_BOX(topBar), GTK_WIDGET(topBar_middle_side));
    gtk_widget_set_name(GTK_WIDGET(topBar_middle_side), "middle_box");
    gtk_widget_set_size_request(GTK_WIDGET(topBar_middle_side), (int)((60.0 / 100.0) * WIN_WIDTH), -1);

    stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 500);

    GtkWidget *product_page = createProductPage();
    gtk_widget_set_size_request(GTK_WIDGET(product_page), WIN_WIDTH, WIN_HEIGHT - 80); 
    
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
    
    gtk_widget_set_name(GTK_WIDGET(homeButton), "home");
    gtk_widget_set_name(GTK_WIDGET(productsButton), "products");
    gtk_widget_set_name(GTK_WIDGET(aboutButton), "about_us");
    gtk_widget_set_name(GTK_WIDGET(contactUsButton), "contact_us");
    
    g_signal_connect(homeButton, "clicked", G_CALLBACK(switch_stack_page), stack);
    g_signal_connect(productsButton, "clicked", G_CALLBACK(switch_stack_page), stack);
    
    topBar_right_side = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_end(GTK_BOX(topBar), topBar_right_side, FALSE, FALSE, 10);
    gtk_widget_set_size_request(GTK_WIDGET(topBar_right_side), (int)((15.0 / 100.0) * WIN_WIDTH), -1);
    gtk_widget_set_name(GTK_WIDGET(topBar_right_side), "right_side");
    
    loginSignUpButton = gtk_button_new_with_label("Login/Signup");
    gtk_button_set_relief(GTK_BUTTON(loginSignUpButton), GTK_RELIEF_NONE);
    gtk_box_pack_start(GTK_BOX(topBar_right_side), GTK_WIDGET(loginSignUpButton), FALSE, FALSE, 0);
    gtk_widget_set_name(GTK_WIDGET(loginSignUpButton), "loginButton");
    ;
    cartButton = gtk_button_new();
    gtk_button_set_relief(GTK_BUTTON(cartButton), GTK_RELIEF_NONE);
    
    GdkPixbuf *cartBuf = gdk_pixbuf_new_from_file_at_scale("../src/img/cart.png", 35, 40, TRUE, NULL);
    
    cartLogo = gtk_image_new_from_pixbuf(cartBuf);
    g_object_unref(cartBuf);
    gtk_button_set_image(GTK_BUTTON(cartButton), GTK_WIDGET(cartLogo));
    gtk_box_pack_end(GTK_BOX(topBar_right_side), cartButton, FALSE, FALSE, 0);
    
    //----------{[End of nav bar and start of main content]}------------

    pageContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(mainContainer), pageContainer);
    // gtk_widget_set_name(GTK_WIDGET(pageContainer), "try1");
    gtk_widget_set_size_request(GTK_WIDGET(pageContainer), WIN_WIDTH, WIN_HEIGHT - 80);
    
    home = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(home), -1, WIN_HEIGHT - 80);
    
    
    scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    // gtk_widget_set_name(GTK_WIDGET(scrolledWindow), "scrolledWindow");
    gtk_box_pack_start(GTK_BOX(home), scrolledWindow, TRUE, TRUE, 0);
    
    contentBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(scrolledWindow), contentBox);
    gtk_widget_set_name(GTK_WIDGET(contentBox), "contentBox");
    // gtk_widget_set_size_request(GTK_WIDGET(contentBox), WIN_WIDTH, WIN_HEIGHT - 8);
    
    gtk_stack_add_titled(GTK_STACK(stack), home, "home", "Home");
    gtk_stack_add_titled(GTK_STACK(stack), product_page, "products", "Products");

    GdkPixbuf *pixBuf = gdk_pixbuf_new_from_file_at_scale("../src/img/MainPicture_1.jpg", WIN_WIDTH, WIN_HEIGHT - 80, FALSE, NULL);
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

    // addItem = gtk_button_new_from_icon_name("tab-new", GTK_ICON_SIZE_BUTTON);
    // gtk_widget_set_size_request(GTK_WIDGET(addItem), 20, 20);
    // gtk_box_pack_start(GTK_BOX(TrendingAddContainer), addItem, FALSE, FALSE, 0);
    // gtk_widget_set_halign(GTK_WIDGET(addItem), GTK_ALIGN_START);

    TrendingContainer = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(TrendingContainer), GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);
    gtk_box_pack_start(GTK_BOX(contentBox), TrendingContainer, FALSE, TRUE, 0);
    gtk_widget_set_name(GTK_WIDGET(TrendingContainer), "featuredContainer");

    TrendingBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(TrendingContainer), TrendingBox);
    gtk_widget_set_size_request(GTK_WIDGET(TrendingBox), WIN_WIDTH, 300);
    gtk_widget_set_name(TrendingBox, "trendingBox");

    if (dataBaseEmpty == TRUE)
    {
        emptyBox = createBox_with_text(300, -1, "No Items Available Currently.", GTK_ORIENTATION_VERTICAL, "newBox"); 
        gtk_box_pack_start(GTK_BOX(TrendingBox), emptyBox, FALSE, FALSE, 0);
        gtk_widget_set_margin_start(GTK_WIDGET(emptyBox), 10);
    }
    else
    {
        emptyBox = NULL;
        // loadItemBox(TrendingBox, product);
    }


    // g_signal_connect(addItem, "clicked", G_CALLBACK(addItemToBox), TrendingBox);

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
    gtk_widget_set_size_request(GTK_WIDGET(offerBox), WIN_WIDTH, 300);
    gtk_widget_set_name(GTK_WIDGET(offerBox), "featuredBox");

    gtk_box_pack_start(GTK_BOX(pageContainer), stack, FALSE, FALSE, 0);

    char *exe_dir = g_path_get_dirname(g_get_prgname());
    char *cssPath = g_build_filename(exe_dir, "../src/css/style.css", NULL);

    GtkCssProvider *css_provider = gtk_css_provider_new();
    GError *error = NULL;
    gtk_css_provider_load_from_path(css_provider, cssPath, &error);
    if (error)
    {
        g_printerr("error loading css file: %s\n", error->message);
        g_error_free(error);
    }

    GtkStyleContext *context = gtk_widget_get_style_context(mainWindow);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(css_provider);
    // g_signal_connect(window, "destroy", G_CALLBACK(printText), NULL);

    g_free(cssPath);
    g_free(exe_dir);

    gtk_widget_show_all(mainWindow);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("test.gtkproject", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
}