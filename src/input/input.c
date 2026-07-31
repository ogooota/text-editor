#include <input/input.h>
#include <input/input_event_queue.h>

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

static input_event_queue mod_event_q;

/**
 * Input even queue implementation
 */
bool
input_event_queue_init(input_event_queue *q)
{
  if (!q)
    return false;

  memset(q, 0, sizeof(*q));

  return true;
}

void
input_event_queue_clear(input_event_queue *q)
{
  if (!q)
    return;

  memset(q, 0, sizeof(*q));
}

bool
input_event_queue_push(input_event_queue *q, input_event ev)
{
  if (!q || q->size >= INPUT_EVENT_QUEUE_MAX_EVENTS)
    return false;

  q->data[q->tail] = ev;
  q->size++;

  q->tail =
    (q->tail + 1) % INPUT_EVENT_QUEUE_MAX_EVENTS;

  return true;
}

bool
input_event_queue_pop(input_event_queue *q, input_event *out_ev)
{
  if (!q || !out_ev || q->size == 0)
    return false;

  *out_ev = q->data[q->head];
  q->size--;

  q->head =
    (q->head + 1) % INPUT_EVENT_QUEUE_MAX_EVENTS;

  return true;
}

bool
input_event_queue_peek(input_event_queue *q, input_event *out_ev)
{
  if (!q || !out_ev || q->size == 0)
    return false;

  *out_ev = q->data[q->head];

  return true;
}

/**
 * Input event queue implementation END
 */

int
input_read_byte(unsigned char *c)
{
  if (!c)
    return -1;

  ssize_t read_bytes;

  do
  {
    read_bytes = read(STDIN_FILENO, c, 1);
  }
  while (read_bytes < 0 && errno == EINTR);

  return (read_bytes >= 0) ? read_bytes : -1;
}

bool
input_poll_event()
{
  input_event ev;
  memset(&ev, 0, sizeof(ev));

  if (input_read_byte(&ev.c) < 0)
    return false;

  switch (ev.c)
  {
    case 27:
    {
      ev.c         = 0;
      ev.key       = KEY_TYPE_ESC;
      ev.ctl_flags = INPUT_EVENT_FLAG_NONE;
    } break;

    case '\r':
    case '\n':
    {
      ev.c         = '\n';
      ev.key       = KEY_TYPE_ENTER;
      ev.ctl_flags = INPUT_EVENT_FLAG_NONE;
    } break;

    case 127:
    case '\b':
    {
      ev.c         = 0;
      ev.key       = KEY_TYPE_BACKSPACE;
      ev.ctl_flags = INPUT_EVENT_FLAG_NONE;
    } break;

    default:
    {
      if (ev.c >= 32 && ev.c <= 126)
      {
        ev.key       = KEY_TYPE_CHARACTER;
        ev.ctl_flags = INPUT_EVENT_FLAG_NONE;
      }
      else if (ev.c >= 1 && ev.c <= 26)
      {
        ev.key       = KEY_TYPE_CHARACTER;
        ev.c         = (ev.c + 'a') - 1;
        ev.ctl_flags = INPUT_EVENT_FLAG_CTRL;
      }
      else
      {
        ev.key       = KEY_TYPE_NONE;
        ev.ctl_flags = INPUT_EVENT_FLAG_NONE;
      }
    } break;
  }

  if (ev.key == KEY_TYPE_NONE)
    return true;

  // verify if ESC, to read escape sequences
  // ...

  // return
  return input_event_queue_push(&mod_event_q, ev);
}

bool
input_event_next(input_event *out_ev)
{
  if (!out_ev || mod_event_q.size == 0)
    return false;

  return input_event_queue_pop(&mod_event_q, out_ev);
}
