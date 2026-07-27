#include "cursor.h"
#include "editor_mode.h"

/**
 * @brief Definition for the main editor structure
 */
struct Editor {
  b8 running;
  struct Cursor cursor;
  enum EditorMode mode;
};

/* Starts the editor */
b8 editor_init(struct Editor *editor);

/* Stops the editor */
b8 editor_stop(struct Editor *editor);
