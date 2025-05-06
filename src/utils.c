#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "structManager.h"

char *int_to_string(int number)
{
    char *buffer = malloc(sizeof(int));
    if(buffer)
    {
        snprintf(buffer, 20, "%d", number);
    }

    return buffer;
}

gboolean validateItem(const char *itemImagePath, const char *itemName, const char *itemPrice)
{
    if(itemImagePath == NULL || strlen(itemImagePath) == 0) return FALSE;
    if(itemName == NULL || strlen(itemImagePath) == 0) return FALSE;
    if(itemPrice == NULL || strlen(itemPrice) == 0) return FALSE;
    return TRUE;
}