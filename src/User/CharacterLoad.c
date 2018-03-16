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
#include "CharacterLoad.h"

////////////////////////////////////////////////////////////
// MySQL Load char
////////////////////////////////////////////////////////////
void CharacterLoad(struct userData * User, char * userName)
{
	struct Connector * DataBase = CurrentConnector();
	MYSQL_RES * Result          = NULL;
	MYSQL_ROW * Row             = NULL;
	char * Position             = NULL;

	//	Copy name
	//strcpy(&userName, &User->Name);

	/*
	*	USER_INIT_TABLE
	*/
	Result = MySQLQuery(DataBase, "SELECT * FROM `%s` WHERE name='%s'", USER_INIT_TABLE, userName);
	Row    = FetchRows(DataBase, Result);

	User->ID                   = GetRowInt(Row, 0);
	User->origChar.WeaponAnim  = GetRowInt(Row, 2);
	User->origChar.Body        = GetRowInt(Row, 3);
	User->origChar.HelmentAnim = GetRowInt(Row, 4);
	User->Class                = GetRowInt(Row, 5);
	User->Desc                 = GetRowChar(Row, 6);
	User->origChar.ShieldAnim  = GetRowInt(Row, 7);
	User->Genero               = GetRowInt(Row, 8);
	User->origChar.Head        = GetRowInt(Row, 9);
	User->origChar.Heading     = GetRowInt(Row, 10);
	User->City                 = GetRowInt(Row, 11);
	User->LastIP               = GetRowChar(Row, 12);
	User->Logged               = GetRowInt(Row, 13);
	User->Password             = GetRowChar(Row, 14);
	Position                   = GetRowChar(Row, 15);
	User->Raza                 = GetRowInt(Row, 16);

	//	Realse
	QueryRealese(DataBase, (MYSQL_RES *)Result);

	/*
	*	USER_FLAGS_TABLE
	*/
	Result = MySQLQuery(DataBase, "SELECT * FROM `%s` WHERE id='%d'", USER_FLAGS_TABLE, User->ID);
	Row    = FetchRows(DataBase, Result);

	User->Flags.Ban            = GetRowInt(Row, 1);
	User->Flags.Desnudo        = GetRowInt(Row, 2);
	User->Flags.Envenenado     = GetRowInt(Row, 3);
	User->Flags.Escondido      = GetRowInt(Row, 4);
	User->Flags.Hambre         = GetRowInt(Row, 5);
	User->Flags.Sed            = GetRowInt(Row, 6);
	User->Flags.LastMap        = GetRowInt(Row, 7);
	User->Flags.Muerto         = GetRowInt(Row, 8);
	User->Flags.Navegando      = GetRowInt(Row, 9);
	User->Flags.Paralizado     = GetRowInt(Row, 10);

	//	Realse
	QueryRealese(DataBase, (MYSQL_RES *)Result);

	/*
	*	USER_FACCION_TABLE
	*/
	Result = MySQLQuery(DataBase, "SELECT * FROM `%s` WHERE id='%d'", USER_FLAGS_TABLE, User->ID);
	Row = FetchRows(DataBase, Result);

	User->Faccion.CiudKill     = GetRowInt(Row, 1);
	User->Faccion.CrimKill     = GetRowInt(Row, 2);
	User->Faccion.Caos         = GetRowInt(Row, 3);
	User->Faccion.Real         = GetRowInt(Row, 4);
	User->Faccion.Date         = GetRowChar(Row, 5);
	User->Faccion.EntryKills   = GetRowInt(Row, 6);
	User->Faccion.Next         = GetRowInt(Row, 7);
	User->Faccion.EntryLevel   = GetRowInt(Row, 8);
	User->Faccion.RARCaos      = GetRowInt(Row, 9);
	User->Faccion.RARReal      = GetRowInt(Row, 10);
	User->Faccion.RECCaos      = GetRowInt(Row, 11);
	User->Faccion.RECReal      = GetRowInt(Row, 12);
	User->Faccion.Reenlist     = GetRowInt(Row, 13);
	User->Faccion.REXCaos      = GetRowInt(Row, 14);
	User->Faccion.RECReal      = GetRowInt(Row, 15);

	//	Realse
	QueryRealese(DataBase, (MYSQL_RES *)Result);

	/*
	*	USER_DEAD_TABLE
	*/
	Result = MySQLQuery(DataBase, "SELECT * FROM `%s` WHERE id='%d'", USER_DEAD_TABLE, User->ID);
	Row = FetchRows(DataBase, Result);

	User->Stats.NPCsKill       = GetRowInt(Row, 1);
	User->Stats.UserKill       = GetRowInt(Row, 2);

	//	Realse
	QueryRealese(DataBase, (MYSQL_RES *)Result);

	/*
	*	USER_REPUTATION_TABLE
	*/
	Result = MySQLQuery(DataBase, "SELECT * FROM `%s` WHERE id='%d'", USER_REPUTATION_TABLE, User->ID);
	Row = FetchRows(DataBase, Result);

	User->Reputation.Asesiono  = GetRowInt(Row, 1);
	User->Reputation.Bandido   = GetRowInt(Row, 2);
	User->Reputation.Burguesia = GetRowInt(Row, 3);
	User->Reputation.Ladrones  = GetRowInt(Row, 4);
	User->Reputation.Nobles    = GetRowInt(Row, 5);
	User->Reputation.Plebe     = GetRowInt(Row, 6);
	User->Reputation.Promedio  = GetRowInt(Row, 7);

	//	Realse
	QueryRealese(DataBase, (MYSQL_RES *)Result);

	/*
	*	USER_STATS_TABLE
	*/
	Result = MySQLQuery(DataBase, "SELECT * FROM `%s` WHERE id='%d'", USER_STATS_TABLE, User->ID);
	Row = FetchRows(DataBase, Result);

	User->Stats.ExpNext        = GetRowInt(Row, 1);
	User->Stats.Level          = GetRowInt(Row, 2);
	User->Stats.Exp            = GetRowInt(Row, 3);
	User->Stats.Gold           = GetRowInt(Row, 4);
	User->Stats.maxAGU         = GetRowInt(Row, 5);
	User->Stats.maxHAM         = GetRowInt(Row, 6);
	User->Stats.maxHIT         = GetRowInt(Row, 7);
	User->Stats.maxHP          = GetRowInt(Row, 8);
	User->Stats.maxMan         = GetRowInt(Row, 9);
	User->Stats.maxSTA         = GetRowInt(Row, 10);
	User->Stats.minAGU         = GetRowInt(Row, 11);
	User->Stats.minHAM         = GetRowInt(Row, 12);
	User->Stats.minHIT         = GetRowInt(Row, 13);
	User->Stats.minHP          = GetRowInt(Row, 14);
	User->Stats.minMan         = GetRowInt(Row, 15);
	User->Stats.minSTA         = GetRowInt(Row, 16);
	User->Stats.SKAvailable    = GetRowInt(Row, 17);
	User->Stats.bankGold       = GetRowInt(Row, 18);

	//	Realse
	QueryRealese(DataBase, (MYSQL_RES *)Result);

	/*
	*	USER_COUTERS_TABLE
	*/
	Result = MySQLQuery(DataBase, "SELECT * FROM `%s` WHERE id='%d'", USER_COUTERS_TABLE, User->ID);
	Row = FetchRows(DataBase, Result);

	User->Counters.Pena        = GetRowInt(Row, 1);
	User->Counters.SKAssigned  = GetRowInt(Row, 2);

	//	Realse
	QueryRealese(DataBase, (MYSQL_RES *)Result);

	/*
	FALTAN->
			user_banco
			user_atributos
			user_hechizos
			user_inventory
			user_mascotas
			user_skills
	*/
}

////////////////////////////////////////////////////////////
// User connect
////////////////////////////////////////////////////////////
void User_Connect(struct userData * User, char * userName)
{

	//	User logged
	if (User->Logged)
	{
		//SendMsg -> "User logged"
		return;
	}
}