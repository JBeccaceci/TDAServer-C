/**
*	 _____ ___   _     ___
*	|_   _|   \ /_\   / __| ___ _ ___ _____ _ _
*	  | | | |) / _ \  \__ \/ -_) '_\ V / -_) '_|
*	  |_| |___/_/ \_\ |___/\___|_|  \_/\___|_|
*		 Tierras de Argentum Server v1.0
*			 Juan Beccaceci <Wildem>
**/
#define _CRT_SECURE_NO_WARNINGS
#include "Map.h"

////////////////////////////////////////////////////////////
/// Map init
////////////////////////////////////////////////////////////
int InitializeMap()
{
	//	Maps
	if ((arrMap = (struct mapBlock ***)malloc(MAX_NUM_MAP * sizeof(struct mapBlock))) == NULL)
	{
		return MAP_ERROR;
	}

	//	Axis
	for (int i = 1; i <= MAP_MAX_SIZE_X; i++)
	{
		//	X
		if ((arrMap[i] = (struct mapBlock **) malloc(MAP_MAX_SIZE_X * sizeof(struct mapBlock))) == NULL)
		{
			return MAP_ERROR;
		}

		//	Y
		for (int j = 1; j <= MAP_MAX_SIZE_Y; j++)
		{
			if ((arrMap[i][j] = (struct mapBlock *)malloc(MAP_MAX_SIZE_Y * sizeof(struct mapBlock))) == NULL)
			{
				return MAP_ERROR;
			}
		}
	}

	return MAP_SUCCESS;
}

////////////////////////////////////////////////////////////
/// Deallocate memory map
////////////////////////////////////////////////////////////
void DestroyMap()
{
	//	Axis
	for (int i = 1; i <= MAP_MAX_SIZE_X; i++)
	{
		//	Y
		for (int j = 1; j <= MAP_MAX_SIZE_Y; j++)
		{
			free(arrMap[i][j]);
		}

		//	X
		free(arrMap[i]);
	}

	//	Maps
	free(arrMap);
}

////////////////////////////////////////////////////////////
/// Read .map file
////////////////////////////////////////////////////////////
int LoadMapFile(int mapID)
{
	char mapName[0xFF];
	FILE * mapFile;
	uint8_t ByFlag;

	//	Create mapName
	sprintf_s(mapName, 0xFF, "../Maps/Mapa%d.map", mapID);

	//	Open file
	if (mapFile = fopen(mapName, "rb"))
	{
		//	Seek header
		fseek(mapFile, MAP_HEADER_SIZE, SEEK_SET);

		//	Load map
		for (int j = 1; j <= MAP_MAX_SIZE_Y; j++)
		{
			for (int i = 1; i <= MAP_MAX_SIZE_X; i++)
			{
				//	Read flag
				fread(&ByFlag, sizeof(uint8_t), 1, mapFile);

				//	Read blocked
				if (ByFlag && 1)
				{
					arrMap[mapID][i][j].Blocked = 1;
				}

				//	Read Layer1
				fread(&arrMap[mapID][i][j].Graphics[1], sizeof(short int), 1, mapFile);

				//	Read layer 2
				if (ByFlag && 2)
				{
					fread(&arrMap[mapID][i][j].Graphics[2], sizeof(short int), 1, mapFile);
				}

				//	Read layer 3
				if (ByFlag && 4)
				{
					fread(&arrMap[mapID][i][j].Graphics[3], sizeof(short int), 1, mapFile);
				}

				//	Read layer 4
				if (ByFlag && 8)
				{
					fread(&arrMap[mapID][i][j].Graphics[4], sizeof(short int), 1, mapFile);
				}

				//	Read trigger
				if (ByFlag && 16)
				{
					fread(&arrMap[mapID][i][j].Trigger, sizeof(short int), 1, mapFile);
				}
			}
		}

		//	Close file
		fclose(mapFile);

		return MAP_SUCCESS;
	}

	return MAP_ERROR;
}

////////////////////////////////////////////////////////////
/// Read .inf file
////////////////////////////////////////////////////////////
int LoadInfFile(int mapID)
{
	char mapName[0xFF];
	FILE * mapFile;
	uint8_t ByFlag;
	short int NPCIndex;

	//	Create mapName
	sprintf_s(mapName, 0xFF, "../Maps/Mapa%d.inf", mapID);

	//	Open file
	if (mapFile = fopen(mapName, "rb"))
	{
		//	Seek header
		fseek(mapFile, MAP_INF_HEADER_SIZE, SEEK_SET);

		//	Load map
		for (int j = 1; j <= MAP_MAX_SIZE_Y; j++)
		{
			for (int i = 1; i <= MAP_MAX_SIZE_X; i++)
			{
				//	Read flag
				fread(&ByFlag, sizeof(uint8_t), 1, mapFile);

				//	Read tileExits
				if (ByFlag && 1)
				{
					fread(&arrMap[mapID][i][j].tileExit.Map, sizeof(short int), 1, mapFile);
					fread(&arrMap[mapID][i][j].tileExit.X, sizeof(short int), 1, mapFile);
					fread(&arrMap[mapID][i][j].tileExit.Y, sizeof(short int), 1, mapFile);
				}

				//	Read npcIndex
				if (ByFlag && 2)
				{
					fread(&NPCIndex, sizeof(short int), 1, mapFile);
				}

				//	Read Objects
				if (ByFlag && 4)
				{
					fread(&arrMap[mapID][i][j].objInfo.objectIndex, sizeof(short int), 1, mapFile);
					fread(&arrMap[mapID][i][j].objInfo.Ammount, sizeof(short int), 1, mapFile);
				}
			}
		}

		//	Close file
		fclose(mapFile);

		return MAP_SUCCESS;
	}

	return MAP_ERROR;
}

////////////////////////////////////////////////////////////
/// Load all maps
////////////////////////////////////////////////////////////
int LoadAllMaps()
{
	if (!InitializeMap())
	{
		return MAP_ERROR;
	}

	for (int i = 1; i <= MAX_NUM_MAP; i++)
	{
		//	Message loading
		printf("\rLoading maps: %d%c", ((i * 100) / MAX_NUM_MAP), 37);

		//	Load .map file
		if (!LoadMapFile(i))
		{
			return MAP_ERROR;
		}

		//	Load .inf file
		if (!LoadInfFile(i))
		{
			return MAP_ERROR;
		}
	}

	printf("\n");

	return MAP_SUCCESS;
}

////////////////////////////////////////////////////////////
/// Is valid position
////////////////////////////////////////////////////////////
int Server_ValidPosition(int posMap, int posX, int posY)
{
	int Result = 0;

	if (posMap > 0)
	{
		if (posMap <= MAX_NUM_MAP)
		{
			if (posX > 0 && posX <= MAP_MAX_SIZE_X)
			{
				if (posY > 0 && posY <= MAP_MAX_SIZE_Y)
				{
					Result = 1;
				}
			}
		}
	}

	return Result;
}

////////////////////////////////////////////////////////////
/// Is wather
////////////////////////////////////////////////////////////
int Server_IsWather(int posMap, int posX, int posY)
{
	int Result = 0;

	if (Server_ValidPosition(posMap, posX, posY))
	{
		if (arrMap[posMap][posX][posY].Graphics[1] >= 1505 && arrMap[posMap][posX][posY].Graphics[1] <= 1520 ||
			arrMap[posMap][posX][posY].Graphics[1] >= 5665 && arrMap[posMap][posX][posY].Graphics[1] <= 5680 ||
			arrMap[posMap][posX][posY].Graphics[1] >= 13547 && arrMap[posMap][posX][posY].Graphics[1] <= 13562 ||
			arrMap[posMap][posX][posY].Graphics[2] == 0)
		{
			Result = 1;
		}
	}

	return Result;
}

////////////////////////////////////////////////////////////
/// Legal position
////////////////////////////////////////////////////////////
int Server_LegalPos(int posMap, int posX, int posY, int Wather, int Earth)
{
	int Result = 0;

	if (Server_ValidPosition(posMap, posX, posY))
	{
		if (Wather != 0 && Earth != 0)
		{
			if (arrMap[posMap][posX][posY].Blocked != 0 && arrMap[posMap][posX][posY].userID == 0 && arrMap[posMap][posX][posY].npcID == 0)
			{
				Result = 1;
			}
		}
		else if (Earth != 0 && Wather == 0)
		{
			if (arrMap[posMap][posX][posY].Blocked != 0 && arrMap[posMap][posX][posY].userID == 0 && arrMap[posMap][posX][posY].npcID == 0 && 
				Server_IsWather(posMap, posX, posY) == 0)
			{
				Result = 1;
			}
		}
		else if (Wather != 0 && Earth == 0)
		{
			if (arrMap[posMap][posX][posY].Blocked != 0 && arrMap[posMap][posX][posY].userID == 0 && arrMap[posMap][posX][posY].npcID == 0 &&
				Server_IsWather(posMap, posX, posY) == 1)
			{
				Result = 1;
			}
		}
	}

	return Result;
}

////////////////////////////////////////////////////////////
/// Get valid position
////////////////////////////////////////////////////////////
void Server_ClosestLegalPos(struct worldPos Pos, struct worldPos * nPos, int Wather, int Earth)
{
	int tX     = 0;
	int tY     = 0;
	int tmpPos = 0;
	int tmpY   = 0;
	int Found  = 1;

	//	Start position is valid?
	if (!Server_LegalPos(Pos.Map, Pos.X, Pos.Y, Wather, Earth))
	{
		MemoryCopy(nPos, &Pos, sizeof(struct worldPos));
		return;
	}

	//	Set map
	nPos->Map = Pos.Map;

	//	Keep looping while the position is not legal
	do
	{
		//	Loop through the tiles
		for (tY = Pos.Y - tmpPos; tY < Pos.Y + tmpPos; tY++)
		{
			for (tX = Pos.X - tmpPos; tX < Pos.X + tmpPos; tX++)
			{
				if ((tY = Pos.Y - tmpPos) || (tY = Pos.Y + tmpPos) || (tY = Pos.X - tmpPos) || (tY = Pos.X + tmpPos))
				{
					if (Server_LegalPos(nPos.Map, tX, tY, Wather, Earth))
					{
						nPos->X = tX;
						nPos->Y = tY;
						tX = Pos.X + tmpPos;
						tY = Pos.Y + tmpPos;
						return;
					}
				}
			}
		}

		//	Next tile
		tmpPos++;
		
		//	If we have checked too much, then just leave
		if (tmpPos > 5)
		{
			Found = 0;
			break;
		}

	} while (1);

	//	If no position was found, return empty positions
	if (Found != 1)
	{
		nPos->X = 0;
		nPos->Y = 0;
	}
}
