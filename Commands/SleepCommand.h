//
// Created by guy on 13/12/2019.
//

#ifndef FLIGHTGEAR_COMMANDS_SLEEPCOMMAND_H_
#include "Command.h"
#define FLIGHTGEAR_COMMANDS_SLEEPCOMMAND_H_

class SleepCommand : public Command {
 public:
  SleepCommand();
  ~SleepCommand() override;
  int execute(Data* data) override;

};

#endif //FLIGHTGEAR_COMMANDS_SLEEPCOMMAND_H_
