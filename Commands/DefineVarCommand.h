//
// Created by guy on 13/12/2019.
//

#ifndef FLIGHTGEAR_COMMANDS_DEFINEVARCOMMAND_H_
#include "Command.h"
#define FLIGHTGEAR_COMMANDS_DEFINEVARCOMMAND_H_

class DefineVarCommand : public Command {
 public:
  DefineVarCommand();
  ~DefineVarCommand() override;
  int execute(Data* data) override;
};

#endif //FLIGHTGEAR_COMMANDS_DEFINEVARCOMMAND_H_
