//
// Created by guy on 13/12/2019.
//

#ifndef FLIGHTGEAR_COMMANDS_SLEEPCOMMAND_H_
#include "Command.h"
#define FLIGHTGEAR_COMMANDS_SLEEPCOMMAND_H_

class SleepCommand : public Command {
 public:
  SleepCommand();
  int execute(string* textArr,
              unordered_map<string, Command*>& commandTable,
              unordered_map<string, VarInfo*>& symTableTable,
              unordered_map<string, VarInfo*>& symTableSimulator) override;

};

#endif //FLIGHTGEAR_COMMANDS_SLEEPCOMMAND_H_
