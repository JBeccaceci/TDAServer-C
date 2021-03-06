#ifndef _SYSTEM_TIME
#define _SYSTEM_TIME

////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////
#include <windows.h>

////////////////////////////////////////////////////////////
// System frecuency
////////////////////////////////////////////////////////////
LARGE_INTEGER systemFrecuency;

////////////////////////////////////////////////////////////
// Current time
////////////////////////////////////////////////////////////
LARGE_INTEGER currentTime;

////////////////////////////////////////////////////////////
// Get time (QueryPerformance)
////////////////////////////////////////////////////////////
float getSystemTime();

#endif