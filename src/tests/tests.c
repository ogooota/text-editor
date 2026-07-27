#include <config/defines.h>
#include <file/file.h>
#include <screenbuffer/screenbuffer.h>
#include <commands/commands.h>
#include <logging/asserts.h>
#include <logging/logger.h>

#include "tests.h"

#include <stdio.h>
#include <string.h>

/**
 * @brief Temporary function for debugging a file
 */
static void tests_print_file(struct File *file) {
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
  struct File *file = file_open("test-file-for-open.txt");
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
}

/**
 * @brief Tests for the screen buffer module
 */
void tests_screenbuffermod() {
  struct ScreenBuffer sb;
  screenbuffer_init(&sb);
  ASSERT(&sb != NULL);
  ASSERT(sb.data != NULL);

  printf("width: %d\nheight: %d\n", sb.width, sb.height);
  
  screenbuffer_clear(&sb, ' ');

  printf("printing buffer content:\n");
  screenbuffer_print(sb);

  screenbuffer_place_char(&sb, 5, 5, 'i');

  printf("printing buffer content:\n");
  screenbuffer_print(sb);
  
  screenbuffer_destroy(&sb);
  printf("buffer destroyed\n");
}

/**
 * @brief Tests for the command module
 * WARN: These tests will be temporary, since now I can only test 
 *       whether the commands are being created normally or not.
 */
void tests_commands() {
  struct Command cmd_mov = command_movement(CMD_TYPE_NONE, 1);
  ASSERT(cmd_mov.type == 0);
  // ASSERT(cmd_mov.data.movement.count == 1); <- Correct - logs error message
  ASSERT(cmd_mov.data.movement.count == 0);

  cmd_mov = command_movement(CMD_TYPE_MOVERIGHT, 1);
  ASSERT(cmd_mov.type == CMD_TYPE_MOVERIGHT);
  ASSERT(cmd_mov.data.movement.count == 1);

  struct Command cmd2 = command_change_mode(EDITOR_MODE_INSERT);
  ASSERT(cmd2.data.editor_mode.mode == EDITOR_MODE_INSERT);
}