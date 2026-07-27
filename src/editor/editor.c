#include "editor.h"
#include "cursor.h"

#include <logging/logger.h>

#include <string.h>

/**
 * @brief Creates a zeroed cursor
 */
struct Cursor editor_cursor_create() {
  return (struct Cursor) {
    .x = 0,
    .y = 0
  };
}

/**
 * @brief Moves the cursor 
 * @param cursor A pointer to the cursor structure
 * @param x The x coordinate
 * @param y The y coordinate
 */
void editor_cursor_move(struct Cursor *cursor, u32 x, u32 y) {
  cursor->x = x;
  cursor->y = y;
}

/**
 * @brief Initializes the main editor application
 * @param editor A pointer to the editor structure
 */
b8 editor_init(struct Editor *editor) {
  memset(editor, 0, sizeof(*editor));
  editor->running = TRUE;
  editor->cursor = editor_cursor_create();
  editor->mode = EDITOR_MODE_NORMAL;
  return TRUE;
}

/**
 * @brief Destroys a running instance of the editor
 * @param editor A pointer to the running editor
 */
b8 editor_stop(struct Editor *editor) {
  if (!editor) {
    ERROR("editor_stop: null editor pointer");
    return FALSE;
  }
  // Warning: memset(editor, 0, sizeof(*editor)); <- Maybe this can be done
  editor->running = FALSE;
  editor->cursor.x = 0;
  editor->cursor.y = 0;
  editor->mode = EDITOR_MODE_NONE;
  return TRUE;
}