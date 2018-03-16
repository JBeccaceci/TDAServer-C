#ifndef _NPC_H
#define _NPC_H

////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////
#include "..\MySQL\Default.h"
#include "..\MySQL\MySQL.h"
#include "..\Map\Map.h"
#include "..\General.h"

////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////
#define MAX_DROPS 5
#define MAX_SOUNDS 3 

////////////////////////////////////////////////////////////
// NPC stats
////////////////////////////////////////////////////////////
struct NPCStats
{
	short int MinHP;
	short int MaxHP;
	short int MinHit;
	short int MaxHit;
	short int Def;
	short int MagicResist;
	short int Alineacion;
};

////////////////////////////////////////////////////////////
// NPC flags
////////////////////////////////////////////////////////////
struct NPCFlags
{
	short int Wather;
	short int Earth;
	short int Faccion;
	short int DoubleAttack;
	short int Domable;
	short int Active;
	short int BackUP;
	short int OrigPos;
	short int EffectParalysis;
	short int Sounds[MAX_SOUNDS];
};

////////////////////////////////////////////////////////////
// NPC coach
////////////////////////////////////////////////////////////
struct NPCCoach
{
	char * Name;
	short int NPCIndex;
};

////////////////////////////////////////////////////////////
// NPC data
////////////////////////////////////////////////////////////
struct NPCData
{
	int ID;
	int Number;
	char * Name;
	char * Desc;
	short int Movement;
	struct NPCStats Stat;
	struct NPCFlags Flags;
	struct Char Char;
	short int Type;
	short int Attackable;
	short int Trade;
	short int Hostile;
	short int poison;
	short int Attack;
	short int Evasion;
	short int InvRespawn;
	struct Object * Drop;
	short int NumberSpells;
	int * Spells;
	short int NumberItems;
	struct Object * Items;
	short int NumberNPCs;
	struct NPCCoach * NPCs;
	int Exp;
	int Gold;
	short int ItemsType;
	short int City;
	struct NPCData * nextNode;
};

////////////////////////////////////////////////////////////
// Last node
////////////////////////////////////////////////////////////
struct NPCData * lastNPC;

////////////////////////////////////////////////////////////
// NPCs count
////////////////////////////////////////////////////////////
int npcCount;

////////////////////////////////////////////////////////////
// Initialize npc variables
////////////////////////////////////////////////////////////
void InitializeNPCs();

////////////////////////////////////////////////////////////
// Allocate a new npc
////////////////////////////////////////////////////////////
struct NPCData * NewNPC();

////////////////////////////////////////////////////////////
// Add a new npc
////////////////////////////////////////////////////////////
void AddNPC(struct NPCData * NPC);

////////////////////////////////////////////////////////////
// Find NPC by ID
////////////////////////////////////////////////////////////
struct NPCData * FindNPC(int npcID);

////////////////////////////////////////////////////////////
// Delete NPC
////////////////////////////////////////////////////////////
void DeleteNPC(int npcID);

////////////////////////////////////////////////////////////
// Load NPCs by MySQL
////////////////////////////////////////////////////////////
int NPCsLoad();

#endif