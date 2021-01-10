/////////////////////////////////////////////////////////////////////////
/////////////////////////////// client.c ////////////////////////////////
/////////////////////////////////////////////////////////////////////////

//info: This client.c file of the client process is incharge of  
//      handling the process and incharge on his functions of the socket.

//............................Includes.................................//
//.....................................................................//
#include "client.h"

//............................Functions................................//
//.....................................................................//

int ReadFromArguments(int argc, char*argv[], struct ClientArgs *client_args){
    if (argc != ARGUMENTS) {
        printf("Error: invalid number of arguments(%d instead of %d)\n",(argc - 1), ARGUMENTS);
        exit(EXIT_FAILURE);
    }
    
    else {
        /* get input file path */
        client_args->server_ip= *argv[1];
        client_args->server_port=*argv[2];
        client_args->username=argv[3];
        
        SERVER_ADDRESS_STR=client_args->server_ip;
        SERVER_PORT=client_args->server_port;
        USERNAME=*client_args->username;
        
        check_error(client_args);
    }
    return EXIT_SUCCESS;
}

int check_error(struct ClientArgs* client_args){
    if (strlen(client_args->username)>20) {
        return EXIT_FAILURE;
    }

    for (int i=0; i<strlen(client_args->username); i++) {
        if ((client_args->username[i]>='0' && client_args->username[i]<='9')||(client_args->username[i]>='a'&& client_args->username[i]<='z')|| (client_args->username[i]>='A'&& client_args->username[i]<='Z'))  {
            int t=0;
        }
        
        else{
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
