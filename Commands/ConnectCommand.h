//
// Created by guy on 13/12/2019.
//

#ifndef FLIGHTGEAR_COMMANDS_CONNECTCOMMAND_H_

#include "Command.h"

#define FLIGHTGEAR_COMMANDS_CONNECTCOMMAND_H_

class ConnectCommand : public Command {
 public:
  ConnectCommand();
  int execute(string* textArr,
              unordered_map<string, Command*>& commandTable,
              unordered_map<string, VarInfo*>& symTableUser,
              unordered_map<string, VarInfo*>& symTableSimulator) override;
  
  void openClientServer(const char *ip,int port);
  static void runningClientServer(int client_socket);
};

#endif //FLIGHTGEAR_COMMANDS_CONNECTCOMMAND_H_
