//
// Created by guy on 13/12/2019.
//

#include "OpenServerCommand.h"
#include <thread>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#define XML_SIZE 36

typedef int i;
using namespace std;

OpenServerCommand::OpenServerCommand() = default;

int OpenServerCommand::execute(string* textArr,
                               unordered_map<string, Command*>& commandTable,
                               unordered_map<string, VarInfo*>& symTable) {
  textArr++;
  int portNum = stoi(*textArr);
  try {
    thread newServer(openServer, portNum, symTable);
    newServer.join();
  } catch (string message) {
    cout << message << endl;
  }
  //todo: implement OpenServerCommand::execute
  return 2;
}

void OpenServerCommand::openServer(int portNum, unordered_map<string, VarInfo*> symTable) {
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
  if (bind(socketfd, (struct sockaddr*) &address, sizeof(address)) == -1) {
    throw "ERROR: cannot bind to the IP address";
  }

  //making socket listen to the port
  if (listen(socketfd, 1) == -1) { //can also set to SOMAXCON (max connections)
    throw "ERROR: cannot make socket listen to the port";
  } else {
    std::cout << "Server is now listening ..." << std::endl;
  }

  // accepting a client
  socklen_t size = sizeof(address);
  int client_socket = accept(socketfd, (struct sockaddr*) &address, &size);

  if (client_socket == -1) {
    throw "ERROR: cannot accept client";
  }

  close(socketfd); //closing the listening socket

  //reading from client

  while (true) {
    char buffer[1024] = {0};
    int valRead = read(client_socket, buffer, 1024);
    cout << buffer << endl;
    parseSimulatorInput(buffer, symTable);
  }
}
void OpenServerCommand::parseSimulatorInput(char* buffer, unordered_map<string, VarInfo*> symtable) {
  const char* delimiter = ",";
  char* element;
  string vars[] = {"airspeed-indicator_indicated-speed-kt",
                   "time_warp",
                   "switches_magnetos",
                   "heading-indicator_offset-deg",
                   "altimeter_indicated-altitude-ft",
                   "altimeter_pressure-alt-ft",
                   "attitude-indicator_indicated-pitch-deg",
                   "attitude-indicator_indicated-roll-deg",
                   "attitude-indicator_internal-pitch-deg",
                   "attitude-indicator_internal-roll-deg",
                   "encoder_indicated-altitude-ft",
                   "encoder_pressure-alt-ft",
                   "gps_indicated-altitude-ft",
                   "gps_indicated-ground-speed-kt",
                   "gps_indicated-vertical-speed",
                   "indicated-heading-deg",
                   "magnetic-compass_indicated-heading-deg",
                   "slip-skid-ball_indicated-slip-skid",
                   "turn-indicator_indicated-turn-rate",
                   "vertical-speed-indicator_indicated-speed-fpm",
                   "flight_aileron",
                   "flight_elevator",
                   "flight_rudder",
                   "flight_flaps",
                   "engine_throttle",
                   "current-engine_throttle",
                   "switches_master-avionics",
                   "switches_starter",
                   "active-engine_auto-start",
                   "flight_speedbrake",
                   "c172p_brake-parking",
                   "engine_primer",
                   "current-engine_mixture",
                   "switches_master-bat",
                   "switches_master-alt",
                   "engine_rpm",
  };

  element = strtok(buffer, delimiter);
  VarInfo* v = symtable.at(vars[0]);
  v->setValue(stod(element));

  for (int i = 1; i < XML_SIZE; i++) {
    element = strtok(nullptr, delimiter);
    v = symtable.at(vars[i]);
    v->setValue(stod(element));
  }
}
