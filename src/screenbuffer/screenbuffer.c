#include "screenbuffer.h"

#include <logging/asserts.h>
#include <logging/logger.h>
#include <util/util.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Initializes an instance of a screen buffer
 * @param sb A screen buffer instance
 */
b8 screenbuffer_init(struct ScreenBuffer *sb) {
  memset(sb, 0, sizeof(*sb));
  
  if (get_terminal_dimensions(&sb->width, &sb->height) == FALSE) {
    ERROR("get_terminal_dimensions:");
    return FALSE;
  }
  
  u32 screen_area = (u32)(sb->width * sb->height);
  sb->data = malloc((sizeof(unsigned char) * screen_area) + 1);
  if (!sb->data) {
    ERROR("get_terminal_dimensions: malloc data");
    return FALSE;
  }
  
  sb->data[screen_area] = 0;

  return TRUE;
}

/**
 * @brief Destroys an instance of a screen buffer
 * @param sb A screen buffer instance
 */
void screenbuffer_destroy(struct ScreenBuffer *sb) {
  if (!sb) return;
  memset(sb, 0, sizeof(*sb));
  free(sb->data);
}

/**
 * @brief Places a char in a screen buffer
 * @param sb A pointer to the screen buffer
 * @param x The x coordinate
 * @param y The y coordinate
 * @param c The char to place
 */
b8 screenbuffer_place_char(struct ScreenBuffer *sb, u16 x, u16 y, char c) {
  if (!sb) {
    ERROR("screenbuffer_place_char: null screen buffer");
    return FALSE;
  }

  sb->data[y * sb->width + x] = c;
	     
  return TRUE;
}

/**
 * @brief Clears the screen buffer
 * @param sb A pointer to the screen buffer
 * @param c The char to clear the screen buffer with
 */
b8 screenbuffer_clear(struct ScreenBuffer *sb, char c) {
  if (!sb) {
    ERROR("screenbuffer_clear: null screen buffer");
    return FALSE;
  }
  memset(sb->data, c, sb->width * sb->height);
  return TRUE;
}

/**
 * @brief Shows the screen bufer on the screen
 * @param sb A copy of a screen buffer structure 
 */
void screenbuffer_print(struct ScreenBuffer sb) {
  write(STDOUT_FILENO, sb.data, sb.width * sb.height);
}
