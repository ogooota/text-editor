#include "editor.h"

bool
editor_init(editor *e)
{
  if (!e)
    return false;

  e->running = true;
  e->dirty   = true;
  e->mode    = EDITOR_MODE_INSERT;

  return true;
}
