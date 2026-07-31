#include <input/input.h>
#include <editor/editor.h>
#include <terminal/terminal.h>

#include <unistd.h>

static editor g_editor = { 0 };

int
main(void)
{
  if (!terminal_enable_raw_mode())
    return -1;

  editor_init(&g_editor);

  input_event ev;
  while (g_editor.running)
  {
    // call input module
    input_poll_event();

    while (input_event_next(&ev))
    {
      if (ev.key == KEY_TYPE_CHARACTER)
        write(1, &ev.c, 1);

      if (ev.key == KEY_TYPE_ESC)
        g_editor.running = false;
    }
  }

  terminal_restore();

  return 0;
}
