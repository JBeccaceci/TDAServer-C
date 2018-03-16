/**
*	 _____ ___   _     ___
*	|_   _|   \ /_\   / __| ___ _ ___ _____ _ _
*	  | | | |) / _ \  \__ \/ -_) '_\ V / -_) '_|
*	  |_| |___/_/ \_\ |___/\___|_|  \_/\___|_|
*		 Tierras de Argentum Server v1.0
*			 Juan Beccaceci <Wildem>
**/
#include "..\Thread.h"

////////////////////////////////////////////////////////////
/// Internal thread funcion
////////////////////////////////////////////////////////////
unsigned int __stdcall InternalRoutine(void * Data);

////////////////////////////////////////////////////////////
/// Create a new thread
////////////////////////////////////////////////////////////
void Thread_Create(platformThread ThreadID, ThreadRoutine Routine, void * ThreadData)
{
	//	New thread
	struct threadData * Thread = malloc(sizeof(struct threadData));
	Thread->Routine            = Routine;
	Thread->Data               = ThreadData;

	//	Create the thread
	ThreadID = (platformThread)(_beginthreadex(NULL, 0, &InternalRoutine, Thread, 0, NULL));
}

////////////////////////////////////////////////////////////
/// Internal thread funcion
////////////////////////////////////////////////////////////
unsigned int __stdcall InternalRoutine(void * Data)
{
	//	Get the thread data
	struct threadData * Thread = (struct threadData *)Data;

	//	Call thread funcion
	Thread->Routine(Thread->Data);

	return 0;
}

////////////////////////////////////////////////////////////
/// Wait the thread
////////////////////////////////////////////////////////////
void Thread_Wait(platformThread ThreadID)
{
	if (ThreadID)
	{
		WaitForSingleObject(ThreadID, INFINITE);
		CloseHandle(ThreadID);
	}
}

////////////////////////////////////////////////////////////
/// Terminate thread by ID
////////////////////////////////////////////////////////////
void Thread_Terminate(platformThread ThreadID)
{
	if (ThreadID)
	{
		TerminateThread(ThreadID, 0);
	}
}