#pragma once

/**
 * @brief Defines all possible modes for the editor
 */
enum EditorMode {
  EDITOR_MODE_NONE = 0,
  EDITOR_MODE_NORMAL,
  EDITOR_MODE_INSERT,
  EDITOR_MODE_VISUAL_CHAR,
  EDITOR_MODE_VISUAL_LINE,
  EDITOR_MODE_SIZE,
};
