#ifndef _LIST_USER_H
#define _LIST_USER_H

////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////
#include "..\Network\SocketDefine.h"
#include "..\Thread\Thread.h"
#include "..\Protocol\ByteBuffer.h"
#include "..\Protocol\BinaryServer.h"
#include "..\Mutex\Mutex.h"
#include "..\Network\Socket.h"
#include "..\General.h"

////////////////////////////////////////////////////////////
/// Atributos num
////////////////////////////////////////////////////////////
#define NUM_ATRIBUTOS 5

////////////////////////////////////////////////////////////
/// Skills num
////////////////////////////////////////////////////////////
#define NUM_SKILLS 20

////////////////////////////////////////////////////////////
/// Spells num
////////////////////////////////////////////////////////////
#define MAX_USER_SPELLS 35

////////////////////////////////////////////////////////////
// Thread struct
////////////////////////////////////////////////////////////
struct userThread
{
	platformThread handleThread;
};

////////////////////////////////////////////////////////////
// User stats
////////////////////////////////////////////////////////////
struct userStats
{
	int minHP;
	int maxHP;
	int maxMan;
	int minMan;
	int minSTA;
	int maxSTA;
	int minHIT;
	int maxHIT;
	int minAGU;
	int maxAGU;
	int maxHAM;
	int minHAM;
	int AsignedSkills;
	long Gold;
	long bankGold;
	int SKAvailable;
	double Exp;
	int Level;
	long ExpNext;
	int NPCsKill;
	int UserKill;
	short int Atr[NUM_ATRIBUTOS];
	short int AtrBK[NUM_ATRIBUTOS];
	short int Skills[NUM_SKILLS];
	short int Spells[MAX_USER_SPELLS];
};

////////////////////////////////////////////////////////////
// User flags
////////////////////////////////////////////////////////////
struct userFlags
{
	short int Ban;
	short int Desnudo;
	short int Envenenado;
	short int Escondido;
	short int Hambre;
	short int Sed;
	short int LastMap;
	short int Muerto;
	short int Paralizado;
	short int Navegando;
};

////////////////////////////////////////////////////////////
// User faccion
////////////////////////////////////////////////////////////
struct userFaccion
{
	int CiudKill;
	int CrimKill;
	short int Caos;
	short int Real;
	char * Date;
	int EntryKills;
	short int Next;
	short int EntryLevel;
	short int RARCaos;
	short int RARReal;
	short int RECReal;
	short int RECCaos;
	short int Reenlist;
	short int REXCaos;
	short int REXReal;
};

////////////////////////////////////////////////////////////
// User reputation
////////////////////////////////////////////////////////////
struct userRep
{
	int Asesiono;
	int Bandido;
	int Burguesia;
	int Ladrones;
	int Nobles;
	int Plebe;
	int Promedio;
};

////////////////////////////////////////////////////////////
// User counters
////////////////////////////////////////////////////////////
struct userCounters
{
	short int Pena;
	short int SKAssigned;
};

////////////////////////////////////////////////////////////
// User struct
////////////////////////////////////////////////////////////
struct userData
{
	int                 ID;
	char *              Name;
	char *              Desc;
	char *              EMail;
	char *              Password;
	char *              LastIP;
	short int           Logged;
	enum eClass         Class;
	enum eRaza          Raza;
	enum eGenero        Genero;
	enum eCity          City;
	struct userCounters Counters;
	struct userRep      Reputation;
	struct userFaccion  Faccion;
	struct userStats    Stats;
	struct userFlags    Flags;
	struct Char         userChar;
	struct Char         origChar;
	struct worldPos     Position;
	struct socketAccept socketData;
	struct userData *   nextNode;
	struct userThread   threadData;
	Mutex               userMutex;
};

////////////////////////////////////////////////////////////
// Initialize user variables
////////////////////////////////////////////////////////////
void initializeUsers();

////////////////////////////////////////////////////////////
// Allocate a new user
////////////////////////////////////////////////////////////
struct userData * newUser();

////////////////////////////////////////////////////////////
// Add a new user
////////////////////////////////////////////////////////////
void addUser(struct userData * User);

////////////////////////////////////////////////////////////
// Initialize user
////////////////////////////////////////////////////////////
void InitializeUser(struct userData * User);

////////////////////////////////////////////////////////////
// Find node by ID
////////////////////////////////////////////////////////////
struct userData * FindUser(int userID);

////////////////////////////////////////////////////////////
// Check ID used
////////////////////////////////////////////////////////////
int User_FreeID(int ID);

////////////////////////////////////////////////////////////
// Get free ID
////////////////////////////////////////////////////////////
int User_GetFreeID();

////////////////////////////////////////////////////////////
// Delete node
////////////////////////////////////////////////////////////
void DeleteUser(int userID);

////////////////////////////////////////////////////////////
// Parse packet
////////////////////////////////////////////////////////////
void ParsePacket(struct userData * User, struct Buffer * tBuffer, int BufferSize);

////////////////////////////////////////////////////////////
// Last node
////////////////////////////////////////////////////////////
struct userData * lastNode;

////////////////////////////////////////////////////////////
// Num of nodes
////////////////////////////////////////////////////////////
int userCount;

////////////////////////////////////////////////////////////
// User list mutex
////////////////////////////////////////////////////////////
Mutex ListMutex;

////////////////////////////////////////////////////////////
// User close
////////////////////////////////////////////////////////////
void User_Close(struct userData * User);

#endif