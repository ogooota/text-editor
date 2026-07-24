#pragma once

/**
 * Definition for maximum number of characters in a file name
 */
#define FILENAME_MAXSIZE 256

/**
 * Definition for maximum number of characters in a line
 */
#define FILEBUFFER_MAXSIZE 8192

typedef struct File {
    /* File name */
    unsigned char name[FILENAME_MAXSIZE];

    /* File content. Heap allocated */
    unsigned char *content;
} file_t;

/* Opens a file representation with its name and content */
file_t *file_open(const char name[FILENAME_MAXSIZE]);
