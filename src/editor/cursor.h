#pragma once 

#include <config/defines.h>

/**
 * @brief A struct for the user's cursor
 */
struct Cursor {
  u32 x;
  u32 y;
};

/**
 * Warning: Since these functions have to do with the cursor
 * itself, I decided to keep them in this file even though
 * the function names are prefixed with editor_*. I'll do this
 * with what I'll be calling a 'sub-module' for convenience.

 * BTW: Maybe I'll change this later.
 */

/* Creates a zeroed cursor */
struct Cursor editor_cursor_create();

/* Moves the cursor */
void editor_cursor_move(struct Cursor *cursor, u32 x, u32 y);