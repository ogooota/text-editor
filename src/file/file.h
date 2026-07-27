#pragma once

#include <config/defines.h>

/**
 * Definition for maximum number of characters in a file name
 */
#define FILENAME_MAXSIZE 256

/**
 * Definition for maximum number of characters in a line
 */
#define FILEBUFFER_MAXSIZE 8192

struct File {
    /* File name */
    unsigned char name[FILENAME_MAXSIZE];

    /* File content. Heap allocated */
    unsigned char *content;
    
    /* File size, in bytes */
    u64 size;
};

/* Opens a file representation with its name and content */
struct File *file_open(const char name[FILENAME_MAXSIZE]);

/* Replaces the file's content by the new one */
b8 file_edit(struct File *file, const char *new_content, u64 content_size);

/* Overwrites the content of the file abstraction to the OS's filesystem abstraction */
b8 file_save(struct File *file);

/* Closes a file representation */
void file_close(struct File *file);
