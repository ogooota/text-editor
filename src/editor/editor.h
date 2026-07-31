#pragma once

typedef enum editor_mode
{
  EDITOR_MODE_NORMAL = 0,
  EDITOR_MODE_INSERT,
  EDITOR_MODE_VISUAL_CHAR,
  EDITOR_MODE_VISUAL_LINE
} editor_mode;

typedef struct editor
{
  bool        running;
  bool        dirty;
  editor_mode mode;
} editor;

bool
editor_init(editor *e);
void
editor_set_mode(editor_mode mode);
