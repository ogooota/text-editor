#pragma once

#include <stdbool.h>
#include <stdint.h>

bool
terminal_get_dimensions(
    uint16_t *width,
    uint16_t *height
    );
bool
terminal_enable_raw_mode();
void
terminal_restore();

