#ifndef shared_h
#define shared_h

#include <stdio.h>
#include <string.h>

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "environment.h"

const char *parameters[]={};
const char* message_string[]={"CLIENT_REQUEST", "CLIENT_ERROR", "CLIENT_VERSUS", "CLIENT_SETUP", "CLIENT_PLAYER_MOVE", "CLIENT_DISCONNECT", "SERVER_APPROVED", "SERVER_DENIED", "SERVER_MAIN_MENU", "SERVER_INVITE", "SERVER_SETUP_REQUSET", "SERVER_PLAYER_MOVE_REQUEST", "SERVER_GAME_RESULTS", "SERVER_WIN", "SERVER_DRAW", "SERVER_OPPONENT_QUIT", "SERVER_NO_OPPONENT", "TRNS_FAILED"};
char SERVER_ADDRESS_STR;
char SERVER_PORT;
char USERNAME; 

TransferResult_t ReceiveString( char** OutputStrPtr, SOCKET sd);
TransferResult_t SendString( const char *Str, SOCKET sd );
TransferResult_t ReceiveBuffer( char* OutputBuffer, int BytesToReceive, SOCKET sd );
TransferResult_t SendBuffer( const char* Buffer, int BytesToSend, SOCKET sd );
int Identify_Parameters(char *AcceptedStr);
#endif /* shared_h */
