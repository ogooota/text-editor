#include "file.h"

#include "../config/defines.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * TODO: Revision/Tests
 *
 * @brief Opens an abstraction to a file which
 *        contains only the file's name and 
 *        content.
 */
file_t *file_open(const char name[FILENAME_MAXSIZE]) {
    file_t *file = NULL;
    memset(file, 0, sizeof(*file));

    /** 
     * If the file name is greater than FILENAME_MAXSIZE,
     * The only copied content will be FILENAME_MAXSIZE 
     * characters long.
     * 
     * TODO: Make a way of handling this possible error
    */ 
    memcpy(file->name, name, FILENAME_MAXSIZE);

    FILE *f = fopen(name, "r");
    if (!f) {
        perror("fopen");
        return NULL;
    }
    
    /* Buffer to save the content of the file temporarily */
    char file_buffer[FILEBUFFER_MAXSIZE];
    memset(file_buffer, 0, sizeof(file_buffer));

    /* Finding the file size */
    fseek(f, 0, SEEK_END);
    u64 file_size = ftell(f);
    if (file_size < 0) {
        perror("ftell");
        fclose(f);
        return NULL;
    }

    /* Placing cursor back in the beginning of the file */
    rewind(f);

    /* Reading into temp buffer */
    u64 bytes_read = fread(file_buffer, 1, file_size, f);
    if (bytes_read < (u64)file_size) {
        perror("fread");
        fclose(f);
        return NULL;
    }

    /* Null-terminated string */
    file_buffer[bytes_read] = 0;

    /* Closing the file */
    fclose(f);

    /* Copying read content to file content */
    memcpy(file->content, file_buffer, bytes_read);

    return file;
}