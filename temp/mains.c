#include <gtk/gtk.h>

static GtkWidget *home_btn, *settings_btn, *profile_btn;

// Function to create a page
GtkWidget *create_page(const char *label_text) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *label = gtk_label_new(label_text);
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
    return box;
}

// Function to update button states
void update_button_state(GtkWidget *active_button) {
    gtk_widget_set_sensitive(home_btn, TRUE);
    gtk_widget_set_sensitive(settings_btn, TRUE);
    gtk_widget_set_sensitive(profile_btn, TRUE);

    gtk_widget_set_sensitive(active_button, FALSE);
}

// Function to switch stack pages
void switch_stack_page(GtkWidget *widget, gpointer user_data) {
    GtkStack *stack = GTK_STACK(user_data);
    const char *page_name = gtk_widget_get_name(widget);

    if (gtk_stack_get_child_by_name(stack, page_name)) {
        gtk_stack_set_visible_child_name(stack, page_name);
        update_button_state(widget);  // Disable the active button
    } else {
        g_print("Error: Stack child '%s' not found!\n", page_name);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Navigation Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    // Create stack
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 500);

    // Create pages
    GtkWidget *home_page = create_page("Home Page");
    GtkWidget *settings_page = create_page("Settings Page");
    GtkWidget *profile_page = create_page("Profile Page");

    // Add pages to stack
    gtk_stack_add_titled(GTK_STACK(stack), home_page, "home", "Home");
    gtk_stack_add_titled(GTK_STACK(stack), settings_page, "settings", "Settings");
    gtk_stack_add_titled(GTK_STACK(stack), profile_page, "profile", "Profile");

    // Create navigation buttons
    GtkWidget *nav_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    home_btn = gtk_button_new_with_label("Home");
    settings_btn = gtk_button_new_with_label("Settings");
    profile_btn = gtk_button_new_with_label("Profile");

    // Set button names
    gtk_widget_set_name(home_btn, "home");
    gtk_widget_set_name(settings_btn, "settings");
    gtk_widget_set_name(profile_btn, "profile");

    // Connect buttons to switch stack pages
    g_signal_connect(home_btn, "clicked", G_CALLBACK(switch_stack_page), stack);
    g_signal_connect(settings_btn, "clicked", G_CALLBACK(switch_stack_page), stack);
    g_signal_connect(profile_btn, "clicked", G_CALLBACK(switch_stack_page), stack);

    gtk_box_pack_start(GTK_BOX(nav_box), home_btn, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nav_box), settings_btn, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nav_box), profile_btn, TRUE, TRUE, 0);

    // Add navigation bar and stack to main box
    gtk_box_pack_start(GTK_BOX(main_box), nav_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), stack, TRUE, TRUE, 0);

    // Disable "Home" button initially
    update_button_state(home_btn);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
