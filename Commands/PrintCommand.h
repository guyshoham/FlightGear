//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_PRINTCOMMAND_H_
#include "Command.h"
#define MILSTONE1_COMMANDS_PRINTCOMMAND_H_

class PrintCommand : public Command {
 public:
  PrintCommand();
  int execute(string* textArr,
              unordered_map<string, Command*>& commandTable,
              unordered_map<string, VarInfo*>& symTable) override;

};
#endif //MILSTONE1_COMMANDS_PRINTCOMMAND_H_
