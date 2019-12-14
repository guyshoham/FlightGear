//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_OPENSERVERCOMMAND_H_
#define MILSTONE1_COMMANDS_OPENSERVERCOMMAND_H_

#include "Command.h"
class OpenServerCommand : public Command {
 public:
  OpenServerCommand(int index);
  int execute() override;
};

#endif //MILSTONE1_COMMANDS_OPENSERVERCOMMAND_H_
