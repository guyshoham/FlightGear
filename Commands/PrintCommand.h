//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_PRINTCOMMAND_H_
#define MILSTONE1_COMMANDS_PRINTCOMMAND_H_

#include "Command.h"
class PrintCommand : public Command {
 public:
  PrintCommand(int index);
  int execute() override;

};
#endif //MILSTONE1_COMMANDS_PRINTCOMMAND_H_
