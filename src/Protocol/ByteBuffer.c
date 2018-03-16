/**
*	 _____ ___   _     ___
*	|_   _|   \ /_\   / __| ___ _ ___ _____ _ _
*	  | | | |) / _ \  \__ \/ -_) '_\ V / -_) '_|
*	  |_| |___/_/ \_\ |___/\___|_|  \_/\___|_|
*		 Tierras de Argentum Server v1.0
*			 Juan Beccaceci <Wildem>
**/
#include "ByteBuffer.h"

////////////////////////////////////////////////////////////
// Copy byte in a buffer
////////////////////////////////////////////////////////////
void buffer_Copy(struct Buffer * tBuffer, void * Data, int sizeGet)
{
	if ((tBuffer->writePos + sizeGet) <= MAX_BUFFER_SIZE)
	{
		//	Put in buffer
		memcpy(&tBuffer->byteArray[tBuffer->writePos], Data, sizeGet);

		//	Increment copy position
		tBuffer->writePos += sizeGet;
	}
}

////////////////////////////////////////////////////////////
// Get byte of the buffer
////////////////////////////////////////////////////////////
void * buffer_Get(struct Buffer * tBuffer, int sizeGet)
{
	if ((tBuffer->readPos + sizeGet) <= MAX_BUFFER_SIZE)
	{
		//	Get byte data
		void * Data = (void*)(tBuffer->byteArray[tBuffer->readPos]);

		//	Increment read position
		tBuffer->readPos += sizeGet;

		//	Data return
		return Data;
	}

	return NULL;
}

////////////////////////////////////////////////////////////
// Put int
////////////////////////////////////////////////////////////
void buffer_PutInt(struct Buffer * tBuffer, int Val)
{

	buffer_Copy(tBuffer, &Val, INTEGER_MEMORY_SIZE);

}

////////////////////////////////////////////////////////////
// Put long
////////////////////////////////////////////////////////////
void buffer_PutLong(struct Buffer * tBuffer, long Val)
{

	buffer_Copy(tBuffer, &Val, LONG_MEMORY_SIZE);

}

////////////////////////////////////////////////////////////
// Put byte
////////////////////////////////////////////////////////////
void buffer_PutByte(struct Buffer * tBuffer, int Val)
{

	buffer_Copy(tBuffer, &Val, BYTE_MEMORY_SIZE);

}

////////////////////////////////////////////////////////////
// Put float
////////////////////////////////////////////////////////////
void buffer_PutFloat(struct Buffer * tBuffer, float Val)
{

	buffer_Copy(tBuffer, &Val, FLOAT_MEMORY_SIZE);

}

////////////////////////////////////////////////////////////
// Put double
////////////////////////////////////////////////////////////
void buffer_PutDouble(struct Buffer * tBuffer, double Val)
{

	buffer_Copy(tBuffer, &Val, DOUBLE_MEMORY_SIZE);

}

////////////////////////////////////////////////////////////
// Put string
////////////////////////////////////////////////////////////
void buffer_PutString(struct Buffer * tBuffer, char * str)
{

	buffer_PutInt(tBuffer, sizeof(str));

	for (int i = 0; i < sizeof(str); i++)
		buffer_Copy(tBuffer, &str[i], CHAR_MEMORY_SIZE);

}

////////////////////////////////////////////////////////////
// Get int
////////////////////////////////////////////////////////////
int buffer_GetInt(struct Buffer * tBuffer)
{

	return (int)buffer_Get(tBuffer, INTEGER_MEMORY_SIZE);

}

////////////////////////////////////////////////////////////
// Get long
////////////////////////////////////////////////////////////
long buffer_GetLong(struct Buffer * tBuffer)
{
	return (long)buffer_Get(tBuffer, LONG_MEMORY_SIZE);
}

////////////////////////////////////////////////////////////
// Get byte
////////////////////////////////////////////////////////////
int buffer_GetByte(struct Buffer * tBuffer)
{

	return (int)buffer_Get(tBuffer, BYTE_MEMORY_SIZE);

}

////////////////////////////////////////////////////////////
// Get float
////////////////////////////////////////////////////////////
float buffer_GetFloat(struct Buffer * tBuffer)
{

	return *(float*)buffer_Get(tBuffer, LONG_MEMORY_SIZE);

}

////////////////////////////////////////////////////////////
// Get double
////////////////////////////////////////////////////////////
double buffer_GetDouble(struct Buffer * tBuffer)
{

	return *(double*)buffer_Get(tBuffer, DOUBLE_MEMORY_SIZE);

}

////////////////////////////////////////////////////////////
// Get string
////////////////////////////////////////////////////////////
char * buffer_GetString(struct Buffer * tBuffer)
{
	int strSize = buffer_GetInt(tBuffer);
	char * Str  = (char *)malloc(strSize * sizeof(char));
	
	//	Put string
	for (int i = 0; i < strSize; i++)
		Str[i] = (char) buffer_Get(tBuffer, CHAR_MEMORY_SIZE);

	//	End Line
	Str[strSize] = '\0';

	return Str;
}

////////////////////////////////////////////////////////////
// Clean buffer
////////////////////////////////////////////////////////////
void buffer_Clear(struct Buffer * tBuffer)
{

	memset(tBuffer->byteArray, 0, MAX_BUFFER_SIZE);
	tBuffer->readPos  = 0;
	tBuffer->writePos = 0;
	tBuffer->BufferSize = 0;

}

////////////////////////////////////////////////////////////
// Read position
////////////////////////////////////////////////////////////
int buffer_ReadPos(struct Buffer * tBuffer)
{

	return tBuffer->readPos;

}

////////////////////////////////////////////////////////////
// Write position
////////////////////////////////////////////////////////////
int buffer_WritePos(struct Buffer * tBuffer)
{

	return tBuffer->writePos;

}

////////////////////////////////////////////////////////////
// Get buffer capacity
////////////////////////////////////////////////////////////
int buffer_Capacity() { return MAX_BUFFER_SIZE; }

////////////////////////////////////////////////////////////
// Set buffer size
////////////////////////////////////////////////////////////
void buffer_SetSize(struct Buffer * tBuffer, int Size)
{

	tBuffer->BufferSize = Size;

}