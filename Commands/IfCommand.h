//
// Created by guy on 13/12/2019.
//

#ifndef FLIGHTGEAR_COMMANDS_IFCOMMAND_H_
#include "ConditionParser.h"
#define FLIGHTGEAR_COMMANDS_IFCOMMAND_H_

class IfCommand : public ConditionParser {
 public:
  IfCommand();
  ~IfCommand() override;
  int execute(Data* data) override;
};
#endif //FLIGHTGEAR_COMMANDS_IFCOMMAND_H_
