//
// Created by guy on 13/12/2019.
//

#ifndef FLIGHTGEAR_COMMANDS_ASSIGNCOMMAND_H_
#define FLIGHTGEAR_COMMANDS_ASSIGNCOMMAND_H_

#include "Command.h"
class AssignCommand : public Command {
 public:
  AssignCommand();
  ~AssignCommand() override;
  int execute(string* textArr,
              unordered_map<string, Command*>& commandTable,
              unordered_map<string, VarInfo*>& symTableUser,
              unordered_map<string, VarInfo*>& symTableSimulator,
              queue<const char*>&  commandsToSimulator) override;

};
#endif //FLIGHTGEAR_COMMANDS_ASSIGNCOMMAND_H_
