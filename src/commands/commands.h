#pragma once

#include <config/defines.h>
#include <editor/editor_mode.h>

#include "command_type.h"

struct Command {
  enum CommandType type;

  union {
    struct {
      u16 count;
    } movement;

    struct {
      enum EditorMode mode;
    } editor_mode;
  } data;
};

/**
 * Deals with sending command types:
 * - CMD_TYPE_MOVEUP
 * - CMD_TYPE_MOVEDOWN
 * - CMD_TYPE_MOVERIGHT
 * - CMD_TYPE_MOVELEFT
*/
struct Command command_movement(enum CommandType type, u16 count);

/**
 * Deals with sending a command that changes the global editor mode
*/
struct Command command_change_mode(enum EditorMode mode);




