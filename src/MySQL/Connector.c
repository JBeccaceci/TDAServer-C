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
#include "Connector.h"

////////////////////////////////////////////////////////////
// Create connector
////////////////////////////////////////////////////////////
struct Connector * CreateConnector(char * Host, char * User, char * Password, char * DataBase, int Port)
{
	struct Connector * tmpConnector = (struct Connector *) malloc(sizeof(struct Connector));

	tmpConnector->Host = Host;
	tmpConnector->User = User;
	tmpConnector->Password = Password;
	tmpConnector->Port = Port;
	tmpConnector->DataBase = DataBase;
	tmpConnector->Connector = NULL;

	return tmpConnector;
}

////////////////////////////////////////////////////////////
// Destroy connector
////////////////////////////////////////////////////////////
void DestroyConnector(struct Connector * MySQLConnector)
{
	if (MySQLConnector)
	{
		MySQLConnector->Host = NULL;
		MySQLConnector->User = NULL;
		MySQLConnector->Password = NULL;
		MySQLConnector->Port = 0;
		MySQLConnector->DataBase = NULL;
		MySQLConnector->Connector = NULL;
	}
}