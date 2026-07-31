#pragma once

#include <stdatomic.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct screen_buffer
{
  uint16_t       width;
  uint16_t       height;
  unsigned char *data;
} screen_buffer;

bool
screen_buffer_init(screen_buffer *);
void
screen_buffer_destroy(screen_buffer *);
void
screen_buffer_place_char(
    screen_buffer *,
    int,
    int,
    unsigned char
    );
void
screen_buffer_clear(screen_buffer *, unsigned char);
