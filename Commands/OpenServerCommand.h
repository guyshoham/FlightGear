//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_OPENSERVERCOMMAND_H_
#include "Command.h"
#define MILSTONE1_COMMANDS_OPENSERVERCOMMAND_H_

class OpenServerCommand : public Command {
 public:
  OpenServerCommand();
  int execute(string* textArr,
              unordered_map<string, Command*> commandTable,
              unordered_map<string, VarInfo*> symTable) override;
  static void openServer(int portNum, unordered_map<string, VarInfo*> symTable);
  static void parseSimulatorInput(char buffer[1024], unordered_map<string, VarInfo*> symTable);
};

#endif //MILSTONE1_COMMANDS_OPENSERVERCOMMAND_H_
