#include "file.h"

#include <config/defines.h>
#include <logging/logger.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @todo: Revision/Tests
 *
 * @brief Opens an abstraction to a file which
 *        contains only the file's name and 
 *        content.
 * @param name Path of the processed file.
 * @warning This function assumes the file name passed
 *          into the parameter 'name' exists.
 * @return A pointer to the file specified by 'name' path.
 */
struct File *file_open(const char name[FILENAME_MAXSIZE]) {
    /**
     * file_t *file = NULL;
     *                ^^^^
     * This shit is embarassing.
     */
    struct File *file = malloc(sizeof(struct File));
    if (!file) {
        perror("malloc");
        return NULL;
    }

    memset(file, 0, sizeof(*file));

    /** 
     * If the file name is greater than FILENAME_MAXSIZE,
     * The only copied content will be FILENAME_MAXSIZE 
     * characters long.
     * 
     * TODO: Make a way of handling this possible error
     * TODO: -> Edit: The way is obviously the heap, but I'm 
     * still considering the possibility.
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
	free(file);
        fclose(f);
        return NULL;
    }

    file->size = file_size;

    /* Placing cursor back in the beginning of the file */
    rewind(f);

    /* Reading into temp buffer */
    u64 bytes_read = fread(file_buffer, 1, file_size, f);
    if (bytes_read < (u64)file_size) {
        perror("fread");
        free(file);
        fclose(f);
        return NULL;
    }

    /* Null-terminated string */
    file_buffer[bytes_read] = 0;

    /* Closing the file */
    fclose(f);

    /* Heap allocating file's content */
    file->content = malloc((sizeof(char) * bytes_read) + 1);
    if (!file->content) {
        free(file);
        perror("malloc");
        return NULL;
    }

    /* Copying read content to file content */
    memcpy(file->content, file_buffer, bytes_read);

    return file;
}
/**
 * @brief Closes a file
 * @param file A file pointer
 */
void file_close(struct File *file) {
    if (!file) {
        WARN("file_close: NULL FILE");
        return;
    }

    free(file->content);
    free(file);
}

/**
 * @brief Replaces the file's content by the 'new_content' passed in parameters.
 * @param file A file pointer
 * @param new_content A pointer to the new content that is placed into the file
 * @param content_size The size of the content string
 */
b8 file_edit(struct File *file, const char *new_content, u64 content_size) {
    /* Asserting for NULL pointers */
    if (!file || !new_content || content_size == 0) {
        ERROR("NULL FILE OR NULL CONTENT");
        return FALSE;
    }

    /* Reallocating new memory for the new_content */
    unsigned char *reallokd_new = realloc(file->content, (sizeof(unsigned char) * content_size) + 1);
    if (!reallokd_new) {
        /**
         * In this case, the old content of the file is preserved, 
         * so there's no need to free it.
         */
        ERROR("file_edit: REALLOC CONTENT");
        return FALSE;
    }
    
    /* Overwriting old content with the new one */
    memcpy(reallokd_new, new_content, content_size);

    /* The file's content is now the new one */
    file->content = reallokd_new;
    file->size = content_size;

    return TRUE;
}
/**
 * @brief Saves the content of the file abstraction to the actual object held in the user's
 *        filesystem.
 * @param file A file pointer
 */
b8 file_save(struct File *file) {
    /* Asserting for NULL pointers */
    if (!file) {
        ERROR("file_save: NULL FILE POINTER");
        return FALSE;
    }
    
    /* Open original file */
    FILE *f = fopen((const char *)file->name, "wb");
    if (!f) {
        ERROR("file_save: COULD NOT OPEN FILE");
        return FALSE;
    }

    /* Write new content to original file */
    u64 size = fwrite(file->content, sizeof(unsigned char), file->size, f);
    if (size != file->size) {
        ERROR("file_save: COULD NOT WRITE TO FILE");
        return FALSE;
    }
    
    return TRUE;
}
