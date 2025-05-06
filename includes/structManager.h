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
    GtkWidget *imageEntry;
    GtkWidget *defaultImageBox;
    GtkWidget *comboBox;
} NewItem;

typedef struct
{
    int id;
    char *imagePath;
    char *name;
    int price;
    int discount;
    char *category;
    GtkWidget *containerToUpdate;
    GtkWidget *nameField;
    GtkWidget *priceField;
    GtkWidget *discountField;
    GtkWidget *comboBox;
} UpdateItem;

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

typedef struct
{
    GtkWidget *categoryBox;
} CategoryBox;


extern Delete *deleteItem;

extern Products *product;
extern int productCapacity;
extern int productCount;

extern AllCategory *categorys;
extern int categoryCapacity;
extern int categoryCount;

extern CategoryBox *box;

extern NewItem item;
extern NewCategory category;

extern UpdateItem *updatedItem;

void addProduct(int id, const char *ImagePath, const char *name, int price, int discount, const char *category);
void addCategory(int id, char *name);
void PrintProduct();
void printCategory();
void printCategoryBox();

#endif