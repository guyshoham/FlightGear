//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_IFCOMMAND_H_
#define MILSTONE1_COMMANDS_IFCOMMAND_H_

#include "ConditionParser.h"
class IfCommand : public ConditionParser {
 public:
  IfCommand();
  int execute() override;
};
#endif //MILSTONE1_COMMANDS_IFCOMMAND_H_
