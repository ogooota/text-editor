#include "util.h"

#include <logging/logger.h>

#include <unistd.h>
#include <sys/ioctl.h>

/**
 * @brief Returns by parameter the width and height of the terminal
 * @param width A pointer to a variable that will contain the terminal's width
 * @param height A pointer to a variable that will contain the terminal's height
 */
b8 get_terminal_dimensions(u16 *width, u16 *height) {
  struct winsize w;
  if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) < 0) {
    ERROR("could not get terminal dimensions");
    return FALSE;
  }
  *width = (u16)w.ws_col;
  *height = (u16)w.ws_row;
  return TRUE;
}
