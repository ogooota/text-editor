#include "commands.h"

/**
 * @brief Handles command movements such as up, down, left and right
 * @param type The direction to move
 * @param count How many lines to move
 */
struct Command command_movement(enum CommandType type, u16 count) {
  struct Command cmd = {0};
  if (type <= 0 || type >= 5)
    return cmd;

  cmd.type = type;
  cmd.data.movement.count = count;
  return cmd;
}

/**
 * @brief Handles sending a command that changes the editor global mode
 * @param mode The next editor mode
 */
struct Command command_change_mode(enum EditorMode mode) {
  struct Command cmd = {0};
  cmd.type = CMD_TYPE_CHANGEMODE;
  cmd.data.editor_mode.mode = mode;
  return cmd;
}


