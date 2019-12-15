//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_FUNCCOMMAND_H_
#define MILSTONE1_COMMANDS_FUNCCOMMAND_H_

#include <list>
#include "Command.h"
using namespace std;

class FuncCommand : public Command {
  list<Command*> _commandsList;
 public:
  FuncCommand();
  int execute() override;
};

#endif //MILSTONE1_COMMANDS_FUNCCOMMAND_H_
