#ifndef STRUCTMANAGER_H
#define STRUCTMANAGER_H

#include <gtk/gtk.h>

typedef struct
{
    int id;
    char *ImageFile;
    char *name;
    int price;
    int discount;
    char *category;
} Products;

typedef struct
{
    int id;
    char *filename;
    GtkWidget *box;
    GtkWidget *boxContainer;
    Products *products;
} Delete;

typedef struct
{
    char *imagePath;
    char *name;
    int price;
    int discount;
    char *category;
    GtkWidget *nameField;
    GtkWidget *priceField;
    GtkWidget *discountField;
    GtkWidget *destinationBox;
    GtkWidget *addItemWindow;
    GtkWidget *imageEntry;
    GtkWidget *defaultImageBox;
} NewItem;

typedef struct 
{
    int id;
    char *name;
} NewCategory;

typedef struct 
{
    int id;
    char *name;
} AllCategory;

extern Delete *deleteItem;

extern Products *product;
extern int productCapacity;
extern int productCount;

extern AllCategory *categorys;
extern int categoryCapacity;
extern int categoryCount;

extern NewItem item;
extern NewCategory category;

void addProduct(int id, const char *ImagePath, const char *name, int price, int discount);
void addCategory(int id, char *name);
void PrintProduct();
void printCategory();

#endif