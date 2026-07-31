#include <terminal/terminal.h>

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

static struct termios original_terminal;
static bool raw_mode_enabled = false;

bool
terminal_get_dimensions(
    uint16_t *width,
    uint16_t *height
    )
{
  struct winsize w;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) < 0)
    return false;

  *width = (uint16_t)w.ws_col;
  *height = (uint16_t)w.ws_row;

  return true;
}

void
terminal_restore(void)
{
    if (!raw_mode_enabled)
        return;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_terminal) == -1)
        perror("tcsetattr: failed to restore terminal");

    raw_mode_enabled = false;
}

bool
terminal_enable_raw_mode(void)
{
    if (raw_mode_enabled)
        return true;

    if (!isatty(STDIN_FILENO))
    {
        fprintf(stderr, "standard input is not a terminal\n");
        return false;
    }

    if (tcgetattr(STDIN_FILENO, &original_terminal) == -1)
    {
        perror("tcgetattr");
        return false;
    }

    struct termios raw = original_terminal;

    raw.c_iflag &= (tcflag_t) ~(BRKINT |
                               ICRNL   |
                               INPCK   |
                               ISTRIP  |
                               IXON);

    raw.c_oflag &= (tcflag_t) ~OPOST;
    raw.c_cflag |= CS8;
    raw.c_lflag &= (tcflag_t) ~(ECHO  |
                               ICANON |
                               IEXTEN);
    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    {
        perror("tcsetattr: failed to enable raw mode");
        return false;
    }

    raw_mode_enabled = true;

    if (atexit(terminal_restore) != 0)
    {
        fprintf(stderr, "failed to register terminal restoration\n");
        terminal_restore();
        return false;
    }

    return true;
}
