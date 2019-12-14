//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_CONNECTCOMMAND_H_
#define MILSTONE1_COMMANDS_CONNECTCOMMAND_H_

#include "Command.h"
class ConnectCommand : public Command {
 public:
  ConnectCommand(int index);
  int execute() override;
};

#endif //MILSTONE1_COMMANDS_CONNECTCOMMAND_H_
