/**
*	 _____ ___   _     ___
*	|_   _|   \ /_\   / __| ___ _ ___ _____ _ _
*	  | | | |) / _ \  \__ \/ -_) '_\ V / -_) '_|
*	  |_| |___/_/ \_\ |___/\___|_|  \_/\___|_|
*		 Tierras de Argentum Server v1.0
*			 Juan Beccaceci <Wildem>
**/
#include "Log.h"

////////////////////////////////////////////////////////////
// Log add
////////////////////////////////////////////////////////////
void Log(char * Text, enum LogType Type, ...)
{
	char LogPath[0xFF];
	char TextLog[0xFF];

	//	Argument list
	va_list argList;

	//	Start arguments
	va_start(argList, TextLog);

	//	Create string
	vsprintf_s(TextLog, 0xFF, Text, argList);

	//	End arg
	va_end(argList);

	//	Switch logs type
	switch (Type)
	{
		case LogGeneral:
			if (LogFile == NULL)
			{
				sprintf_s(LogPath, 0xFF, "../Logs/General.log");
				LogFile = fopen(LogPath, "w+");
			}

			//	Put Data
			fputs(TextLog, LogFile);
			fputs("\n", LogFile);
			break;

		case LogProtocol:
			break;

		default:
			break;
	}
}

////////////////////////////////////////////////////////////
// Get fileSize
////////////////////////////////////////////////////////////
long FileSize(FILE * FileData)
{
	long Size   = 0;
	int seekPos = ftell(FileData);

	//	Seek end file
	fseek(FileData, 0L, SEEK_END);

	//	Get size
	Size = ftell(FileData);

	//	Seek start file
	fseek(FileData, seekPos, SEEK_SET);

	return Size;
}

////////////////////////////////////////////////////////////
// Destroy logs
////////////////////////////////////////////////////////////
void DestroyLogs()
{

	if (LogFile)
	{
		fclose(LogFile);
	}

}