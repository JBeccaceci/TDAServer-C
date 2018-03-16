/**
*	 _____ ___   _     ___
*	|_   _|   \ /_\   / __| ___ _ ___ _____ _ _
*	  | | | |) / _ \  \__ \/ -_) '_\ V / -_) '_|
*	  |_| |___/_/ \_\ |___/\___|_|  \_/\___|_|
*		 Tierras de Argentum Server v1.0
*			 Juan Beccaceci <Wildem>
**/
#include "SystemTime.h"

////////////////////////////////////////////////////////////
// Get time (QueryPerformance)
////////////////////////////////////////////////////////////
float getSystemTime()
{
	//	Start frecuency
	QueryPerformanceFrequency(&systemFrecuency);

	//	Get time counter
	QueryPerformanceCounter(&currentTime);

	//	Return current time
	return (float)((currentTime.QuadPart * 1000.0f) / systemFrecuency.QuadPart);
}