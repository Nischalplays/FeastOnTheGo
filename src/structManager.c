#include <gtk/gtk.h>
#include <stdio.h>
#include "structManager.h"

Products *product = NULL;
int productCapacity = 0;
int productCount = 0;

AllCategory *categorys = NULL;
int categoryCapacity = 0;
int categoryCount = 0;

NewItem item;
NewCategory category;
Delete *deleteItem;

void addProduct(int id, const char *ImagePath,const char *name, int price, int discount)
{
    if(productCount == productCapacity)
    {
        productCapacity = (productCapacity == 0) ? 2 : productCapacity * 2;
        product = realloc(product, productCapacity * sizeof(Products));
        if(!product)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }

    product[productCount].id = id;
    product[productCount].ImageFile = strdup(ImagePath);
    product[productCount].name = strdup(name);
    product[productCount].price = price;
    product[productCount].discount = discount;
    productCount++;
}

void addNewItem(char *imagePath, char *name, int price)
{

}


void addCategory(int id, char *name)
{
    if(categoryCount == categoryCapacity)
    {
        categoryCapacity = (categoryCount == 0) ? 2 : categoryCapacity * 2;
        categorys = realloc(categorys, categoryCapacity * sizeof(AllCategory));
        if(!categorys)
        {
            printf("memory allocation for category failed.\n");
            exit(1);
        }
    }

    categorys[categoryCount].id = id;
    categorys[categoryCount].name = strdup(name);
    categoryCount++;
}

void PrintProduct()
{
    printf("Product list:\n");
    for (int i = 0; i < productCount; i++)
    {
        printf("%d | %s | %s | %d | %d.\n", product[i].id, product[i].ImageFile, product[i].name, product[i].price, product[i].discount);
    }
}

void printCategory()
{
    printf("Category List:\n");
    for(int i = 0; i < categoryCount; i++)
    {
        printf("Id: %d | Name: %s.\n", categorys[i].id, categorys[i].name);
    }
}

// void productStruct()
// {
//     free(product);
// }
