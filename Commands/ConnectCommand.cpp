//
// Created by guy on 13/12/2019.
//

#include "ConnectCommand.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>

ConnectCommand::ConnectCommand() = default;

int ConnectCommand::execute(string *textArr,
                            unordered_map<string, Command *> &commandTable,
                            unordered_map<string, VarInfo *> &symTable,
                             unordered_map<string, VarInfo*> &symTableSimulator) {
    textArr++;
    const char *ip = (*textArr).c_str();
    textArr++;
    int port = stoi(*textArr);
    textArr -= 2;
    try {
        thread newServer(openClientServer, ip, port);
        newServer.join();
    } catch (string message) {
        cout << message << endl;
    }
    return 3;
}

void ConnectCommand::openClientServer(const char *ip, int port) {
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        throw "Could not create a socket";
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(ip);  //the localhost address
    address.sin_port = htons(port);

    // Requesting a connection with the server on local host with port 5402
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        throw "Could not connect to host server";
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }
}
