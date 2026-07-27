#pragma once 

/**
 * Using bitflags for commands if later I want to
 * stack commands
 */
enum CommandType {
  /* Does nothing */
  CMD_TYPE_NONE      = 0,
  
  /* Moves the cursor up, down, left or right */
  CMD_TYPE_MOVEUP    = (1 << 0),
  CMD_TYPE_MOVEDOWN  = (1 << 1),
  CMD_TYPE_MOVERIGHT = (1 << 2),
  CMD_TYPE_MOVELEFT  = (1 << 3),

  /* Changes the global editor mode */
  CMD_TYPE_CHANGEMODE = (1 << 4),
  
  CMD_TYPE_SIZE,
};