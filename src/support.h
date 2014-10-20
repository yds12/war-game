#ifndef _WARGAME_SUPPORT_H
#define _WARGAME_SUPPORT_H

#define ushort unsigned short

// MACRO FUNCTIONS
//#define ROUND(a) ((int)(a + 0.5))
#define CEIL(a) ROUND(a + 0.5)

// TASK TYPE
#define TASK_NONE 0
#define TASK_MOVE 1
#define TASK_FOLLOW 2
#define TASK_ATTACK 3
#define TASK_BUILDING 4
#define TASK_TRAINUNIT 5

#endif

