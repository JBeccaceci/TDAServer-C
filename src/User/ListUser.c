/**
*	 _____ ___   _     ___
*	|_   _|   \ /_\   / __| ___ _ ___ _____ _ _
*	  | | | |) / _ \  \__ \/ -_) '_\ V / -_) '_|
*	  |_| |___/_/ \_\ |___/\___|_|  \_/\___|_|
*		 Tierras de Argentum Server v1.0
*			 Juan Beccaceci <Wildem>
**/
#include "ListUser.h"

////////////////////////////////////////////////////////////
// Initialize user variables
////////////////////////////////////////////////////////////
void initializeUsers()
{

	lastNode  = NULL;
	userCount = 0;
	
	//	InitializeMutex
	MutexInitialize(&ListMutex);
}

////////////////////////////////////////////////////////////
// Allocate a new user
////////////////////////////////////////////////////////////
struct userData * newUser()
{
	//	Create a new node
	struct userData * tmpUser = (struct userData *)malloc(sizeof(struct userData));

	//	Init mutex
	MutexInitialize(&tmpUser->userMutex);

	//	Return allocate node
	return tmpUser;
}

////////////////////////////////////////////////////////////
// Initialize user
////////////////////////////////////////////////////////////
void InitializeUser(struct userData * User)
{

	User->userChar.Index = 0;

}

////////////////////////////////////////////////////////////
// Add a new user
////////////////////////////////////////////////////////////
void addUser(struct userData * User)
{
	//	Add node in the last position
	User->nextNode = lastNode;
	lastNode       = User;

	//	Increment node
	userCount++;
}

////////////////////////////////////////////////////////////
// Find node by ID
////////////////////////////////////////////////////////////
struct userData * FindUser(int userID)
{
	//	Get first node
	struct userData * tmpNode = lastNode;

	//	Check lastNode
	if (lastNode == NULL)
	{
		return NULL;
	}

	//	Loop nodes
	while (tmpNode->ID != userID)
	{
		if (tmpNode->nextNode == NULL) 
		{

			return NULL;

		} 
		else 
		{

			tmpNode = tmpNode->nextNode;

		}
	}

	return tmpNode;
}

////////////////////////////////////////////////////////////
// Check ID used
////////////////////////////////////////////////////////////
int User_FreeID(int ID)
{
	struct userData * Node = lastNode;
	int Found              = 0;

	while (Node != NULL)
	{
		if (Node->userChar.Index == ID) 
		{

			Found = 1;
			break;

		}
		else 
		{

			Node = Node->nextNode;

		}
	}

	return Found;
}

////////////////////////////////////////////////////////////
// Get free ID
////////////////////////////////////////////////////////////
int User_GetFreeID()
{
	int Count = 1;

	while (User_FreeID(Count) != 0)
	{
		Count++;
	}

	return Count;
}

////////////////////////////////////////////////////////////
// Delete node
////////////////////////////////////////////////////////////
void DeleteUser(int userID)
{
	//	Nodes iterator
	struct userData * currentNode = lastNode;
	struct userData * prevNode    = NULL;
	
	if (lastNode == NULL)
	{
		return;
	}

	//	Lock the mutex
	Mutex_Lock(&ListMutex);
	
	//	Loop nodes
	while (currentNode->ID != userID)
	{
		if (currentNode->nextNode == NULL) 
		{

			return;

		} 
		else 
		{

			prevNode = currentNode;
			currentNode = currentNode->nextNode;

		}
	}

	//	Delete node
	if (currentNode == lastNode) 
	{
		lastNode = lastNode->nextNode;
	} 
	else 
	{
		prevNode->nextNode = currentNode->nextNode;
	}

	//	Decrement cant nodes
	userCount--;
	
	//	Unlock the mutex
	Mutex_Unlock(&ListMutex);
}

////////////////////////////////////////////////////////////
// Parse packet
////////////////////////////////////////////////////////////
void ParsePacket(struct userData * User, struct Buffer * tBuffer, int BufferSize)
{
	int packetID = 0;

	do
	{
		//	Get byte
		packetID = buffer_GetByte(tBuffer);

		//	Packet select
		switch (packetID)
		{
			case NETWORK_PACKET_LOGIN: 
				Char_Login(User, tBuffer);
				break;

			default:
				break;
		}

		//	Exit loop
		if (buffer_ReadPos(tBuffer) >= BufferSize) break;

	} while (1);
}

////////////////////////////////////////////////////////////
// User close
////////////////////////////////////////////////////////////
void User_Close(struct userData * User)
{
	//	Lock mutex
	Mutex_Lock(&User->userMutex);

	//	Save user
	if (User->Logged)
	{
		//	SaveUser

		//	Reset flags
		User->Logged = 0;

		//	EraseChar
		if (User->userChar.Index)
		{
			//	-> EraseChar();
		}
	}

	//	Close socket
	socketClose(User->socketData.socketID);

	//	Delete user of the list
	DeleteUser(User->ID);

	//	Unlock the mutex
	Mutex_Unlock(&User->userMutex);

	//	Wait thread or Terminate?
	//Thread_Wait(&User->threadData.handleThread);
	Thread_Terminate(&User->threadData.handleThread);

	//	Deallocate memory
	free(User);
}
