#pragma once

#include <config/defines.h>

/**
 * @brief Struct that represents an abstraction of the screen
 */
struct ScreenBuffer {
  u16            width; /* Width of the terminal screen */
  u16            height; /* Height of the terminal screen */
  unsigned char *data;   /* Screen data. Mallocd with the area of the terminal */
};

b8 screenbuffer_init(struct ScreenBuffer *sb);

void screenbuffer_destroy(struct ScreenBuffer *sb);

b8 screenbuffer_place_char(struct ScreenBuffer *sb, u16 x, u16 y, char c);
b8 screenbuffer_clear(struct ScreenBuffer *sb, char c);
void screenbuffer_print(struct ScreenBuffer sb);

