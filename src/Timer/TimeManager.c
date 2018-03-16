/**
*	 _____ ___   _     ___
*	|_   _|   \ /_\   / __| ___ _ ___ _____ _ _
*	  | | | |) / _ \  \__ \/ -_) '_\ V / -_) '_|
*	  |_| |___/_/ \_\ |___/\___|_|  \_/\___|_|
*		 Tierras de Argentum Server v1.0
*			 Juan Beccaceci <Wildem>
**/
#include "TimeManager.h"

////////////////////////////////////////////////////////////
// Init timer manager
////////////////////////////////////////////////////////////
void TimerInitialize()
{
	//	Initialize mutex
	MutexInitialize(&TimerMutex);

	//	Start timer
	TimerStart = 1;

	//	Create thread
	Thread_Create(&TimerThread, (ThreadRoutine)&TimerManagerRoutine, NULL);
}

////////////////////////////////////////////////////////////
// Destroy timer manager
////////////////////////////////////////////////////////////
void TimerDestroy()
{
	//	Destroy mutex
	MutexDestroy(&TimerMutex);

	//	End timer
	TimerStart = 0;

	//	Terminate thread
	Thread_Terminate(&TimerThread);
}

////////////////////////////////////////////////////////////
// Timer routine
////////////////////////////////////////////////////////////
void TimerManagerRoutine()
{
	while (TimerStart)
	{
		float Time = getSystemTime();

		//	Lock the mutex
		Mutex_Lock(&TimerMutex);

		for (int i = 0; i < MAX_TIMER_COUT; i++)
		{
			if (TimerManager[i].timeActive != 0.0f)
			{
				if (Time > TimerManager[i].currentTime)
				{
					TimerManager[i].Routine();

					if (TimerManager[i].timeFinish != 0.0f)
					{
						DeleteTimer(i);
					} 
					else 
					{
						TimerManager[i].currentTime = TimerManager[i].timeEnd + Time;
					}
				}
			} 
		}

		//	Unlock the mutex
		Mutex_Unlock(&TimerMutex);
	}
}

////////////////////////////////////////////////////////////
// Timer manager
////////////////////////////////////////////////////////////
int GetTimerSlot()
{
	int timerSlot = -1;

	for (int i = 0; i < MAX_TIMER_COUT; i++)
	{
		if (TimerManager[i].timeActive != 1)
		{
			timerSlot = i;
			break;
		}
	}

	return timerSlot;
}

////////////////////////////////////////////////////////////
// Add a new timer
////////////////////////////////////////////////////////////
void AddTimer(float miliSecondsTime, int TimerFinish, TimerRoutine Routine)
{
	//	AddMutex------->
	//MutexLock();
	
	//	Get Slot
	int timerSlot = GetTimerSlot();

	//	System time
	float Time = getSystemTime();

	//	Set timerData
	if (timerSlot != -1)
	{
		TimerManager[timerSlot].currentTime = Time + miliSecondsTime;
		TimerManager[timerSlot].timeEnd = miliSecondsTime;
		TimerManager[timerSlot].timeActive = 1;
		TimerManager[timerSlot].Routine = Routine;
		TimerManager[timerSlot].timeFinish = TimerFinish;
	}
	
	//	AddMutex------->
	//MutexUnlock();
}

////////////////////////////////////////////////////////////
// Delete timer
////////////////////////////////////////////////////////////
void DeleteTimer(int timerID)
{
	//	AddMutex------->
	//MutexLock();
	
	if (timerID)
	{
		TimerManager[timerID].currentTime = 0;
		TimerManager[timerID].timeEnd = 0;
		TimerManager[timerID].timeActive = 0;
		TimerManager[timerID].Routine = NULL;
		TimerManager[timerID].timeFinish = 0;
	}
	
	//	AddMutex------->
	//MutexUnlock();
}
