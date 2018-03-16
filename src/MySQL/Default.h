#ifndef _DEFAULT_CONNECTOR_H
#define _DEFAULT_CONNECTOR_H

////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////
#include "Connector.h"

////////////////////////////////////////////////////////////
// Define
////////////////////////////////////////////////////////////
#define MYSQL_DEFAULT_HOST "localhost"
#define MYSQL_DEFAULT_USER "root"
#define MYSQL_DEFAULT_PASSWORD "301254"
#define MYSQL_DEFAULT_DB "tdac"
#define MYSQL_DEFAULT_PORT 3306

////////////////////////////////////////////////////////////
// Default connector
////////////////////////////////////////////////////////////
int CreateDefaultConnector();

////////////////////////////////////////////////////////////
// Get default connector
////////////////////////////////////////////////////////////
struct Connector * CurrentConnector();

#endif