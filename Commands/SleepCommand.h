//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_SLEEPCOMMAND_H_
#define MILSTONE1_COMMANDS_SLEEPCOMMAND_H_

#include "Command.h"
class SleepCommand : public Command {
 public:
  SleepCommand(int index);
  int execute() override;

};

#endif //MILSTONE1_COMMANDS_SLEEPCOMMAND_H_
