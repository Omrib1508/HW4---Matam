/////////////////////////////////////////////////////////////////////////
///////////////////////////// client.h ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////


//info: This file contain the Client function declarion which used in
//      the proccess


#ifndef CLIENT_H
#define CLIENT_H

//............................Includes.................................//
//.....................................................................//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <ctype.h>

#include "HardCodedData.h"
#include "environment.h"

//............................Defines..................................//
//.....................................................................//

//...........................Structs...................................//
//.....................................................................//

typedef struct ClientArgs {
    char server_ip;
    char* username;
    char server_port;
}ClientArgs;

int ReadFromArguments(int argc, char*argv[], struct ClientArgs *client_args);
int check_error(struct ClientArgs* client_args);
#endif //    !CLIENT_H


