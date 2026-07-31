#pragma once

#include <input/input.h>

#include <stddef.h>

#define INPUT_EVENT_QUEUE_MAX_EVENTS 64

typedef struct input_event_queue
{
  input_event data[INPUT_EVENT_QUEUE_MAX_EVENTS];
  size_t      head;
  size_t      tail;
  size_t      size;
} input_event_queue;

bool
input_event_queue_init(input_event_queue *);
void
input_event_queue_clear(input_event_queue *);
bool
input_event_queue_push(input_event_queue *, input_event);
bool
input_event_queue_pop(input_event_queue *, input_event *);
bool
input_event_queue_peek(input_event_queue *, input_event *);

