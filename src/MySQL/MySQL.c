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
#include "MySQL.h"

////////////////////////////////////////////////////////////
// Connect MySQL
////////////////////////////////////////////////////////////
int MySQLInitialize(struct Connector * MySQLConn)
{
	int Result = 0;

	if (!MySQLConn->Connector)
	{
		//	Init MySQL
		MySQLConn->Connector = mysql_init(NULL);

		//	Connect MySQL
		if (mysql_real_connect(MySQLConn->Connector, MySQLConn->Host, MySQLConn->User, MySQLConn->Password, MySQLConn->DataBase, MySQLConn->Port, NULL, 0) != NULL)
		{
			if (!mysql_select_db(MySQLConn->Connector, MySQLConn->DataBase))
			{
				Result = 1;
			}
		}
	}

	return Result;
}

////////////////////////////////////////////////////////////
// Destroy MySQL
////////////////////////////////////////////////////////////
void MySQLDestroy(struct Connector * MySQLConn)
{
	if (MySQLConn->Connector)
	{
		mysql_close(MySQLConn->Connector);
		MySQLConn->Connector = NULL;
	}
}

////////////////////////////////////////////////////////////
// MySQL Query
////////////////////////////////////////////////////////////
void * MySQLQuery(struct Connector * MySQLConn, char * Query, ...)
{
	if (MySQLConn->Connector)
	{
		char strQuery[0xFF];

		//	Argument list
		va_list argList;

		//	Start arguments
		va_start(argList, Query);

		//	Create string
		vsprintf_s(strQuery, 0xFF, Query, argList);
		
		//	End arg
		va_end(argList);

		//	Execute query
		if (!mysql_query(MySQLConn->Connector, strQuery))
		{
			//	Get result
			MYSQL_RES * MySQLResult = mysql_store_result(MySQLConn->Connector);

			//	Return result
			return (void *)MySQLResult;

		} else { 

			if (mysql_error(MySQLConn->Connector))
			{
				return NULL;
			}

		}
	}

	return NULL;
}

////////////////////////////////////////////////////////////
// Realese query
////////////////////////////////////////////////////////////
void QueryRealese(struct Connector * MySQLConn, void * MySQLResult)
{
	if (MySQLConn->Connector)
	{
		mysql_free_result((MYSQL_RES *)MySQLResult);
	}
}

////////////////////////////////////////////////////////////
// MySQL fetch rows
////////////////////////////////////////////////////////////
void * FetchRows(struct Connector * MySQLConn, void * MySQLResult)
{
	if (MySQLConn->Connector)
	{
		//	Get rows of the Result
		MYSQL_ROW MySQLRow = mysql_fetch_row((MYSQL_RES *)MySQLResult);

		//	Return generic pointer
		return (void *)MySQLRow;
	}

	return NULL;
}

////////////////////////////////////////////////////////////
// Get num fields
////////////////////////////////////////////////////////////
int NumFields(struct Connector * MySQLConn, void * MySQLResult)
{
	if (MySQLConn->Connector)
	{
		return mysql_num_fields((MYSQL_RES *)MySQLResult);
	}

	return -1;
}

////////////////////////////////////////////////////////////
// Get row int
////////////////////////////////////////////////////////////
int GetRowInt(void * MySQLRow, int Field)
{

	return atoi(((MYSQL_ROW)MySQLRow)[Field]);

}

////////////////////////////////////////////////////////////
// Get row long
////////////////////////////////////////////////////////////
long GetRowLong(void * MySQLRow, int Field)
{

	return atoi(((MYSQL_ROW)MySQLRow)[Field]);

}

////////////////////////////////////////////////////////////
// Get row char[]
////////////////////////////////////////////////////////////
char * GetRowChar(void * MySQLRow, int Field)
{

	return ((MYSQL_ROW)MySQLRow)[Field];

}