//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_DEFINEVARCOMMAND_H_
#include "Command.h"
#define MILSTONE1_COMMANDS_DEFINEVARCOMMAND_H_

class DefineVarCommand : public Command {
 public:
  DefineVarCommand();
  int execute(string* textArr,
              unordered_map<string, Command*> commandTable,
              unordered_map<string, VarInfo*> symTable) override;
};

#endif //MILSTONE1_COMMANDS_DEFINEVARCOMMAND_H_
