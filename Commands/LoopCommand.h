//
// Created by guy on 13/12/2019.
//

#ifndef FLIGHTGEAR_COMMANDS_LOOPCOMMAND_H_
#define FLIGHTGEAR_COMMANDS_LOOPCOMMAND_H_

#include "ConditionParser.h"
class LoopCommand : public ConditionParser {
 public:
  LoopCommand();
  ~LoopCommand() override;
  int execute(Data* data) override;
};
#endif //FLIGHTGEAR_COMMANDS_LOOPCOMMAND_H_
