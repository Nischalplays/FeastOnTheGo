#ifndef MAIN_H
#define MAIN_H

#include <gtk/gtk.h>

typedef enum
{
    ACTION_SAVE,
    ACTION_LOAD
} DataAction;

extern GtkWidget *mainWindow;
extern int WIN_WIDTH;
extern int WIN_HEIGHT;
extern GtkWidget *emptyBox;
extern int dataBaseEmpty;

#endif // !MAIN_H