/**
*
* @author:      Juan Beccaceci <juanbeccaceci@icloud.com>
* @description: Cross platform general functions
* @version:     1.0.0
*
**/
#ifndef PARTFORM_DEF_H
#define PARTFORM_DEF_H

////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////
#include "Platform.h"

////////////////////////////////////////////////////////////
// General defines
////////////////////////////////////////////////////////////
#if (PLATFORM_TYPE == PLATFORM_WINDOWS)
#	include <Windows.h>
#	include <process.h>
typedef HANDLE platformThread;
#else
#	include <pthread.h>
typedef pthread_t platformThread;
#endif

#endif