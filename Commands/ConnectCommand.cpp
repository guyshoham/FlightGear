//
// Created by guy on 13/12/2019.
//

#include <sys/socket.h>
#include <mutex>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <sstream>
#include <cstring>
#include "ConnectCommand.h"
#include "../Expressions/Expression.h"
#include "../Expressions/Calculator.h"

mutex m_send;
ConnectCommand::ConnectCommand() = default;

int ConnectCommand::execute(string* textArr,
                            unordered_map<string, Command*>& commandTable,
                            unordered_map<string, VarInfo*>& symTableUser,
                            unordered_map<string, VarInfo*>& symTableSimulator,
                            queue<const char*>& commandsToSimulator) {
  const char* ip = textArr[_index + 1].c_str();

  //calculating port as an expression
  string value = textArr[_index + 2];
  int portNum;

  auto* interpreter = new Interpreter();
  Expression* expression = nullptr;

  for (pair<string, VarInfo*> element : symTableUser) {
    ostringstream temp;
    temp << element.second->getValue();
    string valueStr = temp.str();
    if (value.find(element.second->getName()) != string::npos) {
      string variable = element.second->getName() + "=" + valueStr;
      interpreter->setVariables(variable);
    }
  }

  expression = interpreter->interpret(value);
  portNum = (int) expression->calculate();
  delete expression;
  delete interpreter;

  try { openClientServer(ip, portNum, commandsToSimulator); } catch (const char* message) { cout << message << endl; }
  return 3;
}

void ConnectCommand::openClientServer(const char* ip, int port, queue<const char*>& commandsToSimulator) {
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
  socklen_t size = sizeof(address);
  int is_connect = connect(client_socket, (struct sockaddr*) &address, size);
  if (is_connect == -1) {
    throw "Could not connect to host server";
  } else {
    cout << "Client is now connected to server" << endl;
    thread clientServer(runningClientServer, client_socket, ref(commandsToSimulator));
    clientServer.detach();
  }
}

void ConnectCommand::runningClientServer(int client_socket, queue<const char*>& commandsToSimulator) {

  while (true) {
    if (!commandsToSimulator.empty()) {
      const char* msg;
      msg = commandsToSimulator.front();
      int is_sent = send(client_socket, msg, strlen(msg), 0);
      if (is_sent == -1) {
        cout << "Error sending message: " << msg << endl;
      } else {
        cout << msg << "(is_sent = " << is_sent << ")" << endl;
      }
      commandsToSimulator.pop();
      //this_thread::sleep_for(0.3s);
    }
  }
}
