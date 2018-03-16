/**
*	 _____ ___   _     ___
*	|_   _|   \ /_\   / __| ___ _ ___ _____ _ _
*	  | | | |) / _ \  \__ \/ -_) '_\ V / -_) '_|
*	  |_| |___/_/ \_\ |___/\___|_|  \_/\___|_|
*		 Tierras de Argentum Server v1.0
*			 Juan Beccaceci <Wildem>
**/
#include "BinaryServer.h"

////////////////////////////////////////////////////////////
// Login char
////////////////////////////////////////////////////////////
void Char_Login(struct userData * User, struct Buffer * tBuffer)
{
	//	Check bufferSize
	if (tBuffer->BufferSize < LOGIN_PACKET_MIN_SIZE)
	{
		Log("Error in packetID: %d. Does not match the size. Min: %d. Recieve: %d.", LOG_TYPE_PROTOCOL, NETWORK_PACKET_LOGIN, LOGIN_PACKET_MIN_SIZE, tBuffer->BufferSize);
		return;
	}

	//	Get data
	char * UserName = buffer_GetString(tBuffer);
	char * Password = buffer_GetString(tBuffer);
	int appMajor = buffer_GetByte(tBuffer);
	int appMinor = buffer_GetByte(tBuffer);
	int Revision = buffer_GetByte(tBuffer);

	//	Clean buffer
	buffer_Clear(tBuffer);
}