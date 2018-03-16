/**
*
* @author:      Juan Beccaceci <juanbeccaceci@icloud.com>
* @description: Mutex class (Unix)
* @version:     1.0.0
*
**/
#ifndef _MUTEX_H
#define _MUTEX_H

////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////
#include <pthread.h>

////////////////////////////////////////////////////////////
// Initialize critical section
////////////////////////////////////////////////////////////
void MutexInitialize();

////////////////////////////////////////////////////////////
// Destroy critical section
////////////////////////////////////////////////////////////
void MutexDestroy();

////////////////////////////////////////////////////////////
// Enter in critial section
////////////////////////////////////////////////////////////
void Mutex_Lock();

////////////////////////////////////////////////////////////
// Release the critial section
////////////////////////////////////////////////////////////
void Mutex_Unlock();

////////////////////////////////////////////////////////////
// Critical section object
////////////////////////////////////////////////////////////
pthread_mutex_t criticalSection;

#endif // -> _MUTEX_H