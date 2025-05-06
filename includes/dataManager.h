#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "itemManager.h"
#include "structManager.h"

extern int noOfDataInDB;

int saveMenuData(NewItem *data, const char *filename);
int updateMenuData(const char *filename, gpointer user_data);
int saveCategoryData(NewCategory *data, char *filename);
int isTableEmpty(const char *filename, const char *tableName);
int loadMenuData(const char *filename);
int loadCategoryData(const char *filename);
int deleteMenuData(const char *filename, int id);
void printMenuData(Products *product, int size);

#endif // !DATAMANAGER_H