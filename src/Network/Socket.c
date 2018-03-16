/**
*	 _____ ___   _     ___
*	|_   _|   \ /_\   / __| ___ _ ___ _____ _ _
*	  | | | |) / _ \  \__ \/ -_) '_\ V / -_) '_|
*	  |_| |___/_/ \_\ |___/\___|_|  \_/\___|_|
*		 Tierras de Argentum Server v1.0
*			 Juan Beccaceci <Wildem>
**/
#define _CRT_SECURE_NO_WARNINGS
#include "Socket.h"

////////////////////////////////////////////////////////////
/// Socket recieve data
////////////////////////////////////////////////////////////
void socketRecieve(void * tmpData);

////////////////////////////////////////////////////////////
// Socket listen
////////////////////////////////////////////////////////////
platformSocket socketListen = 0;

////////////////////////////////////////////////////////////
// Socket thread
////////////////////////////////////////////////////////////
platformThread SocketThread;

////////////////////////////////////////////////////////////
// Socket create
////////////////////////////////////////////////////////////
int socketCreate()
{
	struct sockaddr_in socketAddr;
	int Value = 1;

	//	Create socket
	socketListen = socket(PF_INET, SOCK_STREAM, 0);

	// Setup default options
	if (socketListen != -1)
	{
		// Disable the Nagle algorithm
		int Option = 1;
		if (setsockopt(socketListen, IPPROTO_TCP, TCP_NODELAY, (char*)&Option, sizeof(Option)) == -1)
		{
			Value = 0;
		}
	}

	//	Socket address
	memset(socketAddr.sin_zero, 0, sizeof(socketAddr.sin_zero));
	socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_port = htons(7666);

	//	Set bind socket
	if (bind(socketListen, (struct sockaddr*)&socketAddr, sizeof(socketAddr)) < 0)
		Value = 0;
	
	//	Listen socket
	if (listen(socketListen, 0) == -1)
		Value = 0;

	return Value;
}

////////////////////////////////////////////////////////////
// Listen connections
////////////////////////////////////////////////////////////
void socketLoop()
{
	do {

		//	Loop connections
		if (socketListen != -1)
		{
			struct socketAccept socketData;

			//	Check accept the valid socket
			if (socketAccept(&socketData)) {

				//	Create a new user
				struct userData * User = newUser();

				//	Copy socket data to new user
				memcpy(&User->socketData, &socketData, sizeof(struct socketAccept));

				printf("Accept connection: %d\n", User->socketData.socketID);

				//	Add new User
				addUser(User);

				//	Initialize user
				InitializeUser(User);

				//	TEST-------->
				User->userChar.Index = User_GetFreeID();
				User->ID = User_GetFreeID();
				printf("ID: %d \n", User->userChar.Index);
				//	TEST-------->

				//	Create thread
				Thread_Create(&User->threadData.handleThread, (ThreadRoutine)&socketRecieve, (void*)User);

			} else {

				printf("Error en socketAccept!");

			}

		}
	} while (1);
}

////////////////////////////////////////////////////////////
// Accept connection
////////////////////////////////////////////////////////////
int socketAccept(struct socketAccept * socketData)
{
	struct sockaddr_in  socketAddress;
	int Value = 1;
	platformSocketLenght socketLenght = sizeof(socketAddress);

	//	Accept connection
	socketData->socketID = accept(socketListen, (struct sockaddr*)(&socketAddress), &socketLenght);

	//	Check valid socket
	if (socketData->socketID == -1)
		Value = 0;

	//	Set ipAdress
	socketData->IPAdress = inet_ntoa(socketAddress.sin_addr);

	return Value;
}

////////////////////////////////////////////////////////////
// Init winSock
////////////////////////////////////////////////////////////
void initializeWinsock()
{

	#if (PLATFORM_TYPE == PLATFORM_WINDOWS)
		WSADATA wsData;
		WSAStartup(MAKEWORD(2, 2), &wsData);
	#endif

}

////////////////////////////////////////////////////////////
/// Socket recieve data
////////////////////////////////////////////////////////////
void socketRecieve(void * tmpData)
{
	
	int bytesRecieve = 0;
	char buffRecieve[BUFFER_SIZE];

	//	Create class pointer
	struct userData * User = (struct userData *)tmpData;
	struct Buffer tBuffer;

	//	Check socket
	if (User->socketData.socketID != -1 || User->threadData.handleThread > 0)
	{
		do
		{
			//	Recieve bytes
			bytesRecieve = recv(User->socketData.socketID, buffRecieve, BUFFER_SIZE, 0);

			//	Check return value
			if (bytesRecieve > 0) {

				//	Copy buffer
				buffer_Clear(&tBuffer);
				buffer_SetSize(&tBuffer, bytesRecieve);
				buffer_Copy(&tBuffer, &buffRecieve, bytesRecieve);

				//	Parse packet
				ParsePacket(User, &tBuffer, bytesRecieve);

				//	Clean buffer
				buffer_Clear(&tBuffer);
//
//			} else if (bytesRecieve == 0) {
//
//				User_Close(User);
//				printf("Socket Close \n");
//
//			} else {
//
//				printf("Error en socketRecieve");

			}
			 
		} while (bytesRecieve > 0);
		
		//	Socket close
		User_Close(User);
	}
	
}

////////////////////////////////////////////////////////////
/// Socket listener Thread
////////////////////////////////////////////////////////////
int initializeSocketLoop()
{
	//	Init WinAPI
	initializeWinsock();

	//	Init socket
	if (!socketCreate())
		return 0;

	//	Create thread
	Thread_Create(&SocketThread, (ThreadRoutine)&socketLoop, NULL);

	return 1;
}

////////////////////////////////////////////////////////////
/// Close socket
////////////////////////////////////////////////////////////
void socketClose(int socketID)
{

	closesocket(socketID);

}
