#ifndef environment_h
#define environment_h

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "shared.h"

SOCKET m_socket;



#pragma comment(lib, "Ws2_32.lib")

#define STRINGS_ARE_EQUAL( Str1, Str2 ) ( strcmp( (Str1), (Str2) ) == 0 )

typedef enum { CLIENT_REQUEST, CLIENT_VERSUS, CLIENT_SETUP, CLIENT_PLAYER_MOVE, CLIENT_DISCONNECT, CLIENT_ERROR, SERVER_APPROVED, SERVER_DENIED, SERVER_MAIN_MENU, SERVER_ERROR, SERVER_INVITE, SERVER_SETUP_REQUSET, SERVER_PLAYER_MOVE_REQUEST, SERVER_GAME_RESULTS, SERVER_WIN, SERVER_DRAW, SERVER_OPPONENT_QUIT, TRNS_FAILED, TRNS_SUCCEEDED, TRNS_DISCONNECTED } TransferResult_t;

static DWORD RecvDataThread(void);
static DWORD SendDataThread(void);
void MainClient();

#endif /* environment_h */
