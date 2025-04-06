#include <stdio.h>
#include <gtk/gtk.h>
#include <sqlite3.h>
#include "dataManager.h"
#include "itemManager.h"
#include "structManager.h"

int noOfDataInDB = 0;

int createDataBase(const char *filename)
{
    sqlite3 *db;
    char *errMsg = NULL;
    g_print("file name in create%s\n", filename);
    int rc = sqlite3_open(filename, &db);

    if (rc != SQLITE_OK)
    {
        printf("Can't open database: %s.\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    const char *sqlCreateMenu = "CREATE TABLE IF NOT EXISTS menu ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "name TEXT NOT NULL, "
                      "price REAL NOT NULL, "
                      "discount INT NOT NULL, "
                      "image_path TEXT NOT NULL,"
                      "category TEXT NOT NULL);";
                
    const char *sqlCreateCategory = "CREATE TABLE IF NOT EXISTS category ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT NOT NULL);";

    if(sqlite3_exec(db, sqlCreateMenu, 0, 0, &errMsg) != SQLITE_OK)
    {
        printf("SQL ERROR: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    if(sqlite3_exec(db, sqlCreateCategory, 0, 0, &errMsg) != SQLITE_OK)
    {
        printf("SQL ERROR %s.\n", errMsg);\
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return SQLITE_OK;
}

int isTableEmpty(const char *filename,const char *tableName)
{
    sqlite3 *database;
    sqlite3_stmt *stmt;
    char *err_msg = 0;
    int rowCount = -1;
    int rc = sqlite3_open(filename, &database);

    if (rc != SQLITE_OK)
    {
        printf("Database error: %s\n", sqlite3_errmsg(database));
        sqlite3_close(database);
        return -1;
    }
    createDataBase(filename);

    char *sql;
    if(strcmp(tableName, "menu") == 0)
    {
        sql = "SELECT COUNT(*) FROM menu;";
    }
    else if (strcmp(tableName, "category") == 0)
    {
        sql = "SELECT COUNT(*) FROM category;";
    }
    else
    {
        printf("Invalid table name.\n");
        sqlite3_close(database);
        return -1;
    }

    rc = sqlite3_prepare(database, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        printf("Failed to prepare statement: %s\n.", sqlite3_errmsg(database));
        sqlite3_close(database);
        return -1;
    }

    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        rowCount = sqlite3_column_int(stmt, 0);
        noOfDataInDB = rowCount;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(database);

    return rowCount == 0;
}

int saveMenuData(NewItem *data, const char *filename)
{
    sqlite3 *database;
    int rc = sqlite3_open(filename, &database);

    if (rc != SQLITE_OK)
    {
        printf("Database not found. Creating database...\n");
        return -1;
    }

    createDataBase(filename);

    // Using prepared statement instead of snprintf() to prevent SQL injection
    const char *sql = "INSERT INTO menu (name, price, discount, image_path, category) VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(database));
        sqlite3_close(database);
        return rc;
    }

    printf("Inserting: %s | %.2f | %d | %s | %s\n", 
        data->name, data->price, 
        data->discount, data->imagePath, data->category);

    sqlite3_bind_text(stmt, 1, data->name, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, data->price);
    sqlite3_bind_int(stmt, 3, data->discount);
    sqlite3_bind_text(stmt, 4, data->imagePath, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, data->category, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        printf("SQL error in save: %s\n", sqlite3_errmsg(database));
    }
    else
    {
        printf("Menu Item inserted successfully.\n");
    }

    sqlite3_reset(stmt);
    // }

    sqlite3_finalize(stmt);
    sqlite3_close(database);
    return SQLITE_OK;
}

int saveCategoryData(NewCategory *data, char *filename)
{
    sqlite3 *database;
    sqlite3_stmt *stmt;
    char * err_msg;

    int rc = sqlite3_open(filename, &database);
    if(rc != SQLITE_OK)
    {
        printf("Failed to open database.: %s", sqlite3_errmsg(database));
        sqlite3_close(database);
        return 1;
    }

    createDataBase(filename);

    char *sql = "INSERT INTO category (name) VALUES (?)";

    if(sqlite3_prepare_v2(database, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("failed to prepare statement: %s\n", sqlite3_errmsg(database));
        sqlite3_close(database);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, data->name, -1, SQLITE_STATIC);

    if(sqlite3_step(stmt) != SQLITE_DONE)
    {
        printf("SQL ERROR IN save:%s\n", sqlite3_errmsg(database));
    }
    else{
        printf("Inserted successfully.\n");
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(database);
    return 0;
}

int loadMenuData(const char *filename)
{
    sqlite3 *database;
    sqlite3_stmt *stmt;
    char *err_msg = 0;

    int rc = sqlite3_open(filename, &database);
    if (rc != SQLITE_OK)
    {
        printf("Failed to open Database File: %s\n", sqlite3_errmsg(database));
        sqlite3_close(database);
        return rc;
    }
    printf("successfully opened file at %s\n", filename);

    createDataBase(filename);

    char *sql = "SELECT id, name, price, discount, image_path, category FROM menu;";

    rc = sqlite3_prepare_v2(database, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        printf("Failed to Prepare Statement: %s\n", sqlite3_errmsg(database));
        sqlite3_close(database);
        return rc;
    }

    printf("Menu Items\n");
    int count = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const char *name = (const char *)sqlite3_column_text(stmt, 1);
        int price = sqlite3_column_double(stmt, 2);
        int discount = sqlite3_column_int(stmt, 3);
        const char *image_path = (const char *)sqlite3_column_text(stmt, 4);
        const char *category = (const char *)sqlite3_column_text(stmt, 5);

        addProduct(id, image_path, name, price, discount, category);

        count++;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(database);
    return 0;
}

int loadCategoryData(const char *filename)
{
    sqlite3 *database;
    sqlite3_stmt *stmt;
    char *err_msg = 0;

    int rc = sqlite3_open(filename, &database);
    if(rc != SQLITE_OK)
    {
        printf("failed to open database.\n", sqlite3_errmsg(database));
        sqlite3_close(database);
        return 1;
    }

    char *sql = "SELECT id, name FROM category;";

    if(sqlite3_prepare_v2(database, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("failed to prepare Statement: %s", sqlite3_errmsg(database));
        sqlite3_close(database);
        return 1;
    }

    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        char *name = strdup(sqlite3_column_text(stmt, 1));

        addCategory(id, name);
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(database);
    return 0;

}

int deleteMenuData(const char *filename, int id)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *err_msg = 0;

    int rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK)
    {
        g_print("failed to open database");
        sqlite3_close(db);
        return rc;
    }

    char *sql = "DELETE FROM menu WHERE ID = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if(rc != SQLITE_OK)
    {
        g_print("failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }
    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE)
    {
        g_print("sql error in delete: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        g_print("successfully deleted item of id: %d", id);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

void printMenuData(Products *product, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("Id: %d | Name: %s | Price: %d | Discount: %d | Image Path: %s | Category: %s.\n", product[i].id, product[i].name,
               product[i].price, product[i].discount, product[i].ImageFile, product[i].category);
    }
    printf("finished printing menu data. count: %d\n", i);
}