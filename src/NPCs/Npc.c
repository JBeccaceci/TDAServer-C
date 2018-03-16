/**
*	 _____ ___   _     ___
*	|_   _|   \ /_\   / __| ___ _ ___ _____ _ _
*	  | | | |) / _ \  \__ \/ -_) '_\ V / -_) '_|
*	  |_| |___/_/ \_\ |___/\___|_|  \_/\___|_|
*		 Tierras de Argentum Server v1.0
*			 Juan Beccaceci <Wildem>
**/

////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////
#include "Npc.h"

////////////////////////////////////////////////////////////
// Initialize npc variables
////////////////////////////////////////////////////////////
void InitializeNPCs()
{

	lastNPC = NULL;
	npcCount = 0;

}

////////////////////////////////////////////////////////////
// Allocate a new npc
////////////////////////////////////////////////////////////
struct NPCData * NewNPC()
{
	//	Create a new node
	struct NPCData * tmpNPC = (struct NPCData *)malloc(sizeof(struct NPCData));

	//	Return allocate node
	return tmpNPC;
}

////////////////////////////////////////////////////////////
// Add a new npc
////////////////////////////////////////////////////////////
void AddNPC(struct NPCData * NPC)
{

	//	Add node in the last position
	NPC->nextNode = lastNPC;
	lastNPC       = NPC;

	//	Increment node
	npcCount++;
}

////////////////////////////////////////////////////////////
// Find NPC by ID
////////////////////////////////////////////////////////////
struct NPCData * FindNPC(int npcID)
{
	//	Get first node
	struct NPCData * tmpNode = lastNPC;

	//	Check lastNode
	if (lastNPC == NULL) return NULL;

	//	Loop nodes
	while (tmpNode->Number != npcID)
	{
		if (tmpNode->nextNode == NULL) {

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
// Delete NPC
////////////////////////////////////////////////////////////
void DeleteNPC(int npcID)
{
	//	Nodes iterator
	struct NPCData * currentNode = lastNPC;
	struct NPCData * prevNode = NULL;

	//	Loop nodes
	while (currentNode->Number != npcID)
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
	if (currentNode == lastNPC)
	{

		lastNPC = lastNPC->nextNode;

	}
	else
	{

		prevNode->nextNode = currentNode->nextNode;

	}

	//	Decrement cant nodes
	npcCount--;
}

////////////////////////////////////////////////////////////
// Load NPCs by MySQL
////////////////////////////////////////////////////////////
int NPCsLoad()
{
	struct Connector * DataBase = CurrentConnector();

	//	SQL Query
	MYSQL_ROW * Row = NULL;

	//	Query
	MYSQL_RES * Result = MySQLQuery(DataBase, "SELECT * FROM npcs");

	//	Loop rows
	while ((Row = FetchRows(DataBase, Result)))
	{
		struct NPCData * NPC = NewNPC();

		//	Put data
		NPC->ID = GetRowInt(Row, 0);
		NPC->Number = GetRowInt(Row, 1);
		NPC->Name = GetRowChar(Row, 2);
		NPC->Desc = GetRowChar(Row, 3);
		NPC->Movement = GetRowInt(Row, 4);
		NPC->Flags.Wather = GetRowInt(Row, 5);
		NPC->Flags.Earth = GetRowInt(Row, 6);
		NPC->Flags.DoubleAttack = GetRowInt(Row, 7);
		NPC->Type = GetRowInt(Row, 8);
		NPC->Char.Body = GetRowInt(Row, 9);
		NPC->Char.Head = GetRowInt(Row, 10);
		NPC->Char.Heading = GetRowInt(Row, 11);
		NPC->Attackable = GetRowInt(Row, 12);
		NPC->Trade = GetRowInt(Row, 13);
		NPC->Hostile = GetRowInt(Row, 14);
		NPC->Exp = GetRowLong(Row, 15);
		NPC->poison = GetRowInt(Row, 16);
		NPC->Flags.Domable = GetRowInt(Row, 17);
		NPC->Gold = GetRowLong(Row, 18);
		NPC->Attack = GetRowInt(Row, 19);
		NPC->Evasion = GetRowInt(Row, 20);
		NPC->InvRespawn = GetRowInt(Row, 21);
		NPC->Stat.MaxHP = GetRowInt(Row, 22);
		NPC->Stat.MinHP = GetRowInt(Row, 23);
		NPC->Stat.MaxHit = GetRowInt(Row, 24);
		NPC->Stat.MinHit = GetRowInt(Row, 25);
		NPC->Stat.Def = GetRowInt(Row, 26);
		NPC->Stat.MagicResist = GetRowInt(Row, 27);
		NPC->Stat.Alineacion = GetRowInt(Row, 28);

		/* NUMERO ITEMS BLA BLA */

	}

	return 1;
}