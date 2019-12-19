//
// Created by guy on 13/12/2019.
//

#include "OpenServerCommand.h"
#include <thread>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

using namespace std;

OpenServerCommand::OpenServerCommand() = default;

int OpenServerCommand::execute(string *textArr,
                               unordered_map<string, Command *> commandTable,
                               unordered_map<string, VarInfo *> symTable) {
    textArr++;
    int portNum = stoi(*textArr);
    try {
        thread newServer(openServer, portNum);
        newServer.join();
    } catch (string message) {
        cout << message << endl;
    }
    //todo: implement OpenServerCommand::execute
    return 2;
}

void OpenServerCommand::openServer(int portNum) {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        throw "ERROR: cannot create a socket";
    }
    //bind socket to IP address
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(portNum);

    //the bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        throw "ERROR: cannot bind to the IP address";
    }

    //making socket listen to the port
    if (listen(socketfd, 1) == -1) { //can also set to SOMAXCON (max connections)
        throw "ERROR: cannot make socket listen to the port";
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&address);

    if (client_socket == -1) {
        throw "ERROR: cannot accept client";
    }

    close(socketfd); //closing the listening socket

    //reading from client
    char buffer[1024] = {0};
    int valRead = read( client_socket , buffer, 1024);
    std::cout<<buffer<<std::endl;
}
