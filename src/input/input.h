#pragma once

typedef enum key_type
{
  KEY_TYPE_NONE = 0,

  /* Alphabet */
  KEY_TYPE_A,
  KEY_TYPE_B,
  KEY_TYPE_C,
  KEY_TYPE_D,
  KEY_TYPE_E,
  KEY_TYPE_F,
  KEY_TYPE_G,
  KEY_TYPE_H,
  KEY_TYPE_I,
  KEY_TYPE_J,
  KEY_TYPE_K,
  KEY_TYPE_L,
  KEY_TYPE_M,
  KEY_TYPE_N,
  KEY_TYPE_O,
  KEY_TYPE_P,
  KEY_TYPE_Q,
  KEY_TYPE_R,
  KEY_TYPE_S,
  KEY_TYPE_T,
  KEY_TYPE_U,
  KEY_TYPE_V,
  KEY_TYPE_W,
  KEY_TYPE_X,
  KEY_TYPE_Y,
  KEY_TYPE_Z,

  KEY_TYPE_ENTER,
  KEY_TYPE_BACKSPACE,
  KEY_TYPE_ESC,

  KEY_TYPE_CHARACTER,

  KEY_TYPE_SIZE,
} key_type;

typedef enum input_event_flag
{
  INPUT_EVENT_FLAG_NONE  = 0,
  INPUT_EVENT_FLAG_CTRL  = (1u << 0),
  INPUT_EVENT_FLAG_ALT   = (1u << 1),
  INPUT_EVENT_FLAG_SHIFT = (1u << 2),
} input_event_flag;

typedef struct input_event
{
  key_type         key;
  input_event_flag ctl_flags;
  unsigned char    c;
} input_event;

int
input_read_byte(unsigned char *);
bool
input_poll_event();
bool
input_event_next(input_event *);
