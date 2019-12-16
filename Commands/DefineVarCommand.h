//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_DEFINEVARCOMMAND_H_
#define MILSTONE1_COMMANDS_DEFINEVARCOMMAND_H_

#include "Command.h"
class DefineVarCommand : public Command {
 public:
  DefineVarCommand();
  int execute() override;

};

#endif //MILSTONE1_COMMANDS_DEFINEVARCOMMAND_H_
