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
#include "Default.h"
#include "MySQL.h"

////////////////////////////////////////////////////////////
// Default connector
////////////////////////////////////////////////////////////
struct Connector * DefaultConnector = NULL;

////////////////////////////////////////////////////////////
// Create default connector
////////////////////////////////////////////////////////////
int CreateDefaultConnector()
{
	int Result = 1;

	//	Create default connector
	DefaultConnector = CreateConnector(MYSQL_DEFAULT_HOST, MYSQL_DEFAULT_USER, MYSQL_DEFAULT_PASSWORD, MYSQL_DEFAULT_DB, MYSQL_DEFAULT_PORT);
	
	//	Init SQL
	if (DefaultConnector != NULL) {

		if (MySQLInitialize(DefaultConnector) != 1)
		{
			Result = 0;
		}

	} else {

		Result = 0;

	}

	return Result;
}

////////////////////////////////////////////////////////////
// Get default connector
////////////////////////////////////////////////////////////
struct Connector * CurrentConnector() { return DefaultConnector; }