#!/bin/bash

# Variables
APP_NAME="bin/main"  # Name of the output binary
SOURCE_FILES="src/main.c src/dataManager.c src/itemManager.c src/widgetManager.c src/products.c src/structManager.c"  # List of source files
INCLUDE_DIRS="-I./includes"  # Add xlsxwriter header path
LIBRARIES="-L./libs -L'C:/msys64/ucrt64/lib' -lsqlite3"  # Add xlsxwriter library if it's a compiled lib
CFLAGS=$(pkg-config --cflags gtk+-3.0)  # Get GTK+ flags
LIBS=$(pkg-config --libs gtk+-3.0)      # Get GTK+ libraries

# Compilation
echo "Building $APP_NAME..."
gcc -o $APP_NAME $SOURCE_FILES $INCLUDE_DIRS $CFLAGS $LIBS $LIBRARIES

# Check if build was successful
if [ $? -eq 0 ]; then
    echo "Build succeeded. Run './$APP_NAME' to execute."
else
    echo "Build failed. Please check for errors."
fi
