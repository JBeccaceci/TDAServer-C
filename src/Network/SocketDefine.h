/**
*
* @author:      Juan Beccaceci <juanbeccaceci@icloud.com>
* @description: Cross platform socket declares
* @version:     1.0.0
*
**/
#ifndef SOCKET_DEFINE_H
#define SOCKET_DEFINE_H

////////////////////////////////////////////////////////////
// Define
////////////////////////////////////////////////////////////
#if (PLATFORM_TYPE == PLATFORM_WINDOWS)
#	define WIN32_LEAN_AND_MEAN
#	define _WINSOCK_DEPRECATED_NO_WARNINGS //-> VS 2015
#endif

////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////
#include "../Platform/Platform.h"
#include "../Platform/platformDef.h"

////////////////////////////////////////////////////////////
// Includes and typedef
////////////////////////////////////////////////////////////
#if (PLATFORM_TYPE == PLATFORM_WINDOWS)
#	include <WinSock2.h>
#	include <WS2tcpip.h>
typedef SOCKET platformSocket;
typedef int    platformSocketLenght;
#else
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <netinet/tcp.h>
#	include <arpa/inet.h>
#	include <netdb.h>
#	include <unistd.h>
#	include <errno.h>
typedef int       platformSocket;
typedef socklen_t platformSocketLenght;
#endif

////////////////////////////////////////////////////////////
// Socket struct
////////////////////////////////////////////////////////////
struct socketAccept
{
	platformSocket socketID;
	char * IPAdress;
};

////////////////////////////////////////////////////////////
// Force declare librarys
////////////////////////////////////////////////////////////
#if (PLATFORM_TYPE == PLATFORM_WINDOWS)
#	pragma comment (lib, "Ws2_32.lib")   //-> Win32
#	pragma comment (lib, "Mswsock.lib")  //-> Win32
#endif

#endif // -> SOCKET_DEFINE_H