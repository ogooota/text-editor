#include <screenbuffer/screenbuffer.h>
#include <terminal/terminal.h>

#include <stdlib.h>
#include <string.h>

bool
screen_buffer_init(screen_buffer *sb)
{
  if (!sb)
    return false;

  if (!terminal_get_dimensions(&sb->width, &sb->height))
    return false;

  int area = (int)(sb->width * sb->height);

  sb->data =
    malloc((sizeof(unsigned char) * area) + 1);

  if (!sb->data)
    return false;

  sb->data[area] = 0;

  return true;
}

void
screen_buffer_destroy(screen_buffer *sb)
{
  if (!sb)
    return;

  free(sb->data);
  sb->height = 0;
  sb->width  = 0;
}

void
screen_buffer_place_char(
    screen_buffer *sb,
    int            x,
    int            y,
    unsigned char  c
    )
{
  if (!sb            ||
      !sb->data      ||
      x < 0          ||
      y < 0          ||
      x >= sb->width ||
      y >= sb->height)
    return;

  sb->data[y * sb->width + x] = c;
}

void
screen_buffer_clear(screen_buffer *sb, unsigned char c)
{
  if (!sb || !sb->data)
    return;

  memset(sb->data, c, (sb->width * sb->height));
}


