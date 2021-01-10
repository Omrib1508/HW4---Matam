#include "client.h"

int main(int argc, char* argv[]) {
    int exit_code = EXIT_SUCCESS;
    ClientArgs*        client_args = NULL;
    client_args=(ClientArgs*)malloc(sizeof(ClientArgs));
    ReadFromArguments(argc, argv, client_args);
    MainClient();
}
