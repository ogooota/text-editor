#include <config/defines.h>
#include <file/file.h>
#include <logging/asserts.h>
#include <logging/logger.h>

#include "tests.h"

#include <stdio.h>
#include <string.h>

/**
 * @brief Temporary function for debugging a file
 */
static void tests_print_file(file_t *file) {
  printf( "File name: %s\n"
          "File content: %s\n"
          "File size: %llu bytes\n\n",
          file->name,
          file->content,
          file->size );
}

/**
 * @brief Tests for the file module
 */
void tests_filemod() {
  /* File Open */
  file_t *file = file_open("test-file-for-open.txt");
  ASSERT_MESSAGE(file != NULL, "file_open() error");
  
  /* Simply print the content */
  printf("--- FILE OPEN ---\n");
  tests_print_file(file);
  
  /* File Editing */
  u8 edit_n = 1;
  const char *new_content = "Hello world, banana!";
  u64 size = strlen(new_content);
  b8 done = file_edit(file, new_content, size);
  ASSERT(done == TRUE);

  /* Simply print the content again to verify changes */
  printf("--- FILE EDIT ---\n");
  printf("edited %d times\n", edit_n++);
  tests_print_file(file);

  /* File Editing */
  new_content = "Hello world, banana\n\n\n\nBANANAAAAAAAA!!!!";
  size = strlen(new_content);
  done = file_edit(file, new_content, size);
  ASSERT(done == TRUE);

  /* Simply print the content again to verify changes */
  printf("edited %d times\n", edit_n++);
  tests_print_file(file);
  
  /* File Save */
  printf("--- FILE SAVE ---\n");
  done = file_save(file);
  ASSERT(done == TRUE);
  printf("File saved.\n");

  /* File Close */
  file_close(file);
  ASSERT(file->content == NULL);
}

