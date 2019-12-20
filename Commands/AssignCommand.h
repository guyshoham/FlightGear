//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_ASSIGNCOMMAND_H_
#define MILSTONE1_COMMANDS_ASSIGNCOMMAND_H_

#include "Command.h"
class AssignCommand : public Command {
 public:
  AssignCommand();
  int execute(string* textArr,
              unordered_map<string, Command*>& commandTable,
              unordered_map<string, VarInfo*>& symTableUser,
              unordered_map<string, VarInfo*>& symTableSimulator) override;

};
#endif //MILSTONE1_COMMANDS_ASSIGNCOMMAND_H_
