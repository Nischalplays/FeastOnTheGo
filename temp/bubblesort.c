#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 20
#define BAR_WIDTH 20
#define DELAY 200 // milliseconds (increased for better visualization)

int array[ARRAY_SIZE];
GtkWidget *drawing_area;
int current_index = -1, swap_index = -1;
int sorting = 0;
int i = 0, j = 0; // Ensure sorting variables are global and properly reset

gboolean bubble_sort_step(gpointer data);

gboolean delayed_swap(gpointer data) {
    int temp = array[current_index];
    array[current_index] = array[swap_index];
    array[swap_index] = temp;
    gtk_widget_queue_draw(drawing_area);
    return g_timeout_add(DELAY, bubble_sort_step, NULL);
}

void shuffle_array(GtkWidget *widget, gpointer data) {
    if (sorting) return; // Prevent shuffle during sorting
    for (int i = 0; i < ARRAY_SIZE; i++)
        array[i] = rand() % 200 + 20;
    current_index = -1;
    swap_index = -1;
    i = 0;
    j = 0;
    gtk_widget_queue_draw(drawing_area);
}

void draw_array(cairo_t *cr) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (i == current_index) {
            cairo_set_source_rgb(cr, 1.0, 0.2, 0.2); // Current bar
        } else if (i == swap_index) {
            cairo_set_source_rgb(cr, 0.2, 1.0, 0.2); // Swap bar
        } else {
            cairo_set_source_rgb(cr, 0.2, 0.6, 1.0);
        }
        cairo_rectangle(cr, i * BAR_WIDTH, 300 - array[i], BAR_WIDTH - 2, array[i]);
        cairo_fill(cr);
    }
}

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    if (!GTK_IS_WIDGET(widget)) return FALSE; // Prevent critical errors
    draw_array(cr);
    return FALSE;
}

gboolean bubble_sort_step(gpointer data) {
    if (i < ARRAY_SIZE - 1) {
        if (j < ARRAY_SIZE - i - 1) {
            current_index = j;
            swap_index = j + 1;
            gtk_widget_queue_draw(drawing_area);
            if (array[j] > array[j + 1]) {
                return g_timeout_add(DELAY, delayed_swap, NULL);
            }
            j++;
        } else {
            j = 0;
            i++;
        }
        gtk_widget_queue_draw(drawing_area);
        return TRUE;
    }
    current_index = -1;
    swap_index = -1;
    sorting = 0;
    i = 0; // Reset sorting variables after completion
    j = 0;
    gtk_widget_queue_draw(drawing_area);
    return FALSE;
}

void start_sorting(GtkWidget *widget, gpointer data) {
    if (!sorting) {
        sorting = 1;
        i = 0;
        j = 0;
        g_timeout_add(DELAY, bubble_sort_step, NULL);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    srand(time(NULL));
    shuffle_array(NULL, NULL);
    
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Bubble Sort Visualization");
    gtk_window_set_default_size(GTK_WINDOW(window), ARRAY_SIZE * BAR_WIDTH, 320);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, ARRAY_SIZE * BAR_WIDTH, 300);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), drawing_area, TRUE, TRUE, 0);
    
    GtkWidget *button_sort = gtk_button_new_with_label("Start Sorting");
    g_signal_connect(button_sort, "clicked", G_CALLBACK(start_sorting), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button_sort, FALSE, FALSE, 0);
    
    GtkWidget *button_shuffle = gtk_button_new_with_label("Shuffle");
    g_signal_connect(button_shuffle, "clicked", G_CALLBACK(shuffle_array), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button_shuffle, FALSE, FALSE, 0);
    
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
