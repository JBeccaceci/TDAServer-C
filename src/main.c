/**
*	 _____ ___   _     ___
*	|_   _|   \ /_\   / __| ___ _ ___ _____ _ _
*	  | | | |) / _ \  \__ \/ -_) '_\ V / -_) '_|
*	  |_| |___/_/ \_\ |___/\___|_|  \_/\___|_|
*		 Tierras de Argentum Server v1.0
*			 Juan Beccaceci <Wildem>
**/
#include <stdio.h>
#include "Network\Socket.h"
#include "Timer\SystemTime.h"
#include "Timer\TimeManager.h"
#include "Map\Map.h"
#include "Logs\Log.h"
#include "MySQL\Default.h"
#include "NPCs\Npc.h"

int main(int argc, char **argv)
{

	//	Start!
	printf(" _____ ____  _____    _____                     \n");
	printf("|_   _|    \\|  _  |  |   __|___ ___ _ _ ___ ___ \n");
	printf("  | | |  |  |     |  |__   | -_|  _| | | -_|  _|\n");
	printf("  |_| |____/|__|__|  |_____|___|_|  \\_/|___|_|  \n");
	printf("                                        v1.0.0\n");

	//	Message loading
	printf("\rLoading users: ");

	//	Init users
	initializeUsers();

	//	MsgOk
	printf("OK \n");

	//	Message loading
	printf("\rLoading socket: ");

	//	Socket loop
	initializeSocketLoop();

	//	MsgOk
	printf("OK \n");

	//	Message loading
	printf("\rLoading timers: ");

	//	Timer
	TimerInitialize();

	//	MsgOk
	printf("OK \n");

	//	Message loaging
	printf("\rLoading MySQL: ");

	//	MySQL default connector
	if (CreateDefaultConnector() != 1)
	{
		printf("Error \n");
		exit(0);
	}
	else 
	{
		printf("OK \n");
	}

	//	NPCs test
	NPCsLoad();

	//	Map initialize
	//if (LoadAllMaps() == 0)
	//{
	//	printf("Error! \n");
	//	exit(0);
	//}

	//	Message loading
	printf("Server running... \n");

	while (1)
	{

	}

	return 0;
}