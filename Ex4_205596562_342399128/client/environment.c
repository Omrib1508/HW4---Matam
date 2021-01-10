#include "environment.h"

//Reading data coming from the server
static DWORD RecvDataThread(void){
    TransferResult_t RecvRes;

    while (1)
    {
        
        char *AcceptedStr = NULL;
        RecvRes = ReceiveString( &AcceptedStr , m_socket );
        if (RecvRes==TRNS_FAILED || RecvRes==TRNS_DISCONNECTED) {
            printf("Failed connectiong to server on %c:%c.\n"
                   "Choose what to do next:\n"
                   "1. Try to reconnect\n"
                   "2. Exit\n", SERVER_ADDRESS_STR, SERVER_PORT);
            return 0x555;
        }
        if ( parameters[0] == message_string[7] )
        {
            printf("Server on %c:%c denied the connection request."
                   "\nChoose what to do next:\n"
                   "1. Try to reconnect\n"
                   "2. Exit\n", SERVER_ADDRESS_STR, SERVER_PORT);
            return 0x555;
        }
        else if ( parameters[0] == message_string[6])
        {
            printf("Connected to server on %c:%c\n",SERVER_ADDRESS_STR, SERVER_PORT);
            return 0x555;
        }
        else if (parameters[0] == message_string[17])
        {
            printf("Failed connectiong to server on %c:%c.\n"
                   "Choose what to do next:\n"
                   "1. Try to reconnect\n"
                   "2. Exit\n", SERVER_ADDRESS_STR, SERVER_PORT);
            return 0x555;
        }
        else if (parameters[0] == message_string[8])
        {
            printf("Choose what to do next:\n"
                   "1. Play against another client\n"
                   "2. Quit\n");
            return 0x555;
        }
        else if (parameters[0] == message_string[9])
        {
            printf("Game is on!\n");
            return 0x555;
        }
        else if (parameters[0] == message_string[10])
        {
            printf("Choose your 4 digits:\n");
            return 0x555;
        }
        else if (parameters[0] == message_string[11])
        {
            printf("Choose your guess:\n");
            return 0x555;
        }
        else if (parameters[0]== message_string[12])
        {
            printf("Bulls:%s\n"
                   "Cows:%s\n"
                   "%s played: %s\n",parameters[1],parameters[2], parameters[3], parameters[4]);
            return 0x555;
        }
        else if (parameters[0] == message_string[13])
        {
            printf("%s won!\n"
                   "opponents number was%s\n",parameters[1], parameters[2]);
            return 0x555;
        }
        else if (parameters[0] == message_string[14])
        {
            printf("It's a tie\n");
            return 0x555;
        }
        else if (parameters[0] == message_string[15])
        {
            printf("Opponent quit.\n");
            return 0x555;
        }
        else if (parameters[0] == message_string[16])
        {
            
            printf("Opponent quit.\n");
            return 0x555;
        }
        else
        {
            printf("%s\n",AcceptedStr);
        }
        
        free(AcceptedStr);
    }

    return 0;
}

//Sending data to the server
static DWORD SendDataThread(void)
{
    char SendStr[256];
    TransferResult_t SendRes;
    char *Str;
    
    while (1)
    {
        gets_s(SendStr, sizeof(SendStr)); //Reading a string from the keyboard
        
        if ( STRINGS_ARE_EQUAL(SendStr,"2") ){
            Str=message_string[5];
            strcat(Str, "\n");
            strcpy(SendStr, Str);
            return 0x555; //"quit" signals an exit from the client side
        }
        if ((parameters[0] == message_string[7] || parameters[0]==message_string[17])&& STRINGS_ARE_EQUAL(SendStr,"1")) {
            Str=message_string[0];
            strcat(Str, ":");
            strcat(Str, &USERNAME);
            strcat(Str, "\n");
            strcpy(SendStr, Str);
            return 0x555;
           
        }
        if ((parameters[0] == message_string[8])&& STRINGS_ARE_EQUAL(SendStr,"1")) {
            strcpy(SendStr,message_string[2]);
            strcat(Str, "\n");
            return 0x555; //"quit" signals an exit from the client side
        }
        
        if (parameters[0] == message_string[10]) {
            Str=message_string[3];
            strcat(Str, ":");
            strcat(Str, SendStr);
            strcat(Str, "\n");
            strcpy(SendStr, Str);
            return 0x555; //"quit" signals an exit from the client side
        }
        if (parameters[0] == message_string[11]) {
            Str=message_string[4];
            strcat(Str, ":");
            strcat(Str, SendStr);
            strcat(Str, "\n");
            strcpy(SendStr, Str);
            return 0x555; //"quit" signals an exit from the client side
        }
        SendRes = SendString( SendStr, m_socket);
    
        if ( SendRes == TRNS_FAILED )
        {
            strcpy(SendStr, message_string[0]);
            strcat(SendStr, "\n");
            return 0x555;
        }
    }
    free(parameters);
}

void MainClient()
{
    SOCKADDR_IN clientService;
    HANDLE hThread[2];

    // Initialize Winsock.
    WSADATA wsaData; //Create a WSADATA object called wsaData.
    //The WSADATA structure contains information about the Windows Sockets implementation.
    
    //Call WSAStartup and check for errors.
    int iResult = WSAStartup( MAKEWORD(2, 2), &wsaData );


    //Call the socket function and return its value to the m_socket variable.
    // For this application, use the Internet address family, streaming sockets, and the TCP/IP protocol.
    
    // Create a socket.
    m_socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    // Check for errors to ensure that the socket is a valid socket.
    if ( m_socket == INVALID_SOCKET ) {
        WSACleanup();
        return;
    }
    /*
     The parameters passed to the socket function can be changed for different implementations.
     Error detection is a key part of successful networking code.
     If the socket call fails, it returns INVALID_SOCKET.
     The if statement in the previous code is used to catch any errors that may have occurred while creating
     the socket. WSAGetLastError returns an error number associated with the last error that occurred.
     */


    //For a client to communicate on a network, it must connect to a server.
    // Connect to a server.

    //Create a sockaddr_in object clientService and set  values.
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr( SERVER_ADDRESS_STR ); //Setting the IP address to connect to
    clientService.sin_port = htons( SERVER_PORT ); //Setting the port to connect to.
    
    /*
        AF_INET is the Internet address family.
    */


    // Call the connect function, passing the created socket and the sockaddr_in structure as parameters.
    // Check for general errors.
    if ( connect( m_socket, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR) {
        WSACleanup();
        return;
    }

    // Send and receive data.
    /*
        In this code, two integers are used to keep track of the number of bytes that are sent and received.
        The send and recv functions both return an integer value of the number of bytes sent or received,
        respectively, or an error. Each function also takes the same parameters:
        the active socket, a char buffer, the number of bytes to send or receive, and any flags to use.

    */

    hThread[0]=CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE) SendDataThread,
        NULL,
        0,
        NULL
    );
    hThread[1]=CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE) RecvDataThread,
        NULL,
        0,
        NULL
    );

    WaitForMultipleObjects(2,hThread,FALSE,INFINITE);

    TerminateThread(hThread[0],0x555);
    TerminateThread(hThread[1],0x555);

    CloseHandle(hThread[0]);
    CloseHandle(hThread[1]);
    
    closesocket(m_socket);
    
    WSACleanup();
    
    return;
}

