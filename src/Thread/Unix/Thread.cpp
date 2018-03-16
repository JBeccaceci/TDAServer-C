#include "Thread.h"

////////////////////////////////////////////////////////////
/// Internal thread funcion
////////////////////////////////////////////////////////////
void * InternalRoutine(void * Data);

////////////////////////////////////////////////////////////
/// Create a new thread
////////////////////////////////////////////////////////////
bool Thread_Create(platformThread &ThreadID, ThreadRoutine Routine, void * ThreadData)
{
	//	New thread
	threadData * Thread = new threadData;
	Thread->Routine = Routine;
	Thread->Data = ThreadData;

	//	Create the thread
	ThreadID = pthread_create(&ThreadID, NULL, ThreadRoutine, Thread);

	//	Error?
	if (ThreadID != 0)
		return false;

	return true;
}

////////////////////////////////////////////////////////////
/// Internal thread funcion
////////////////////////////////////////////////////////////
void * InternalRoutine(void * Data)
{
	//	Get the thread data
	threadData * Thread = (threadData *)Data;

	//	Call thread funcion
	Thread->Routine(Thread->Data);
	delete Thread;
}

////////////////////////////////////////////////////////////
/// Terminate thread by ID
////////////////////////////////////////////////////////////
void Thread_Terminate(platformThread ThreadID)
{
	if (ThreadID)
    {
		pthread_cancel(ThreadID);
	}
}