//
// Created by guy on 13/12/2019.
//

#ifndef FLIGHTGEAR_COMMANDS_OPENSERVERCOMMAND_H_
#include "Command.h"
#define FLIGHTGEAR_COMMANDS_OPENSERVERCOMMAND_H_

class OpenServerCommand : public Command {
 public:
  OpenServerCommand();
  ~OpenServerCommand() override;
  int execute(Data* data) override;
  static void openServer(int portNum,
                         unordered_map<string, VarInfo*>& symTableUser,
                         unordered_map<string, VarInfo*>& symTableSimulator);
  static void runningServer(int client_socket,
                            unordered_map<string, VarInfo*>& symTableUser,
                            unordered_map<string, VarInfo*>& symTableSimulator);
  static void parseSimulatorInput(char buffer[1024],
                                  unordered_map<string, VarInfo*>& symTableUser,
                                  unordered_map<string, VarInfo*>& symTableSimulator);
};

#endif //FLIGHTGEAR_COMMANDS_OPENSERVERCOMMAND_H_
