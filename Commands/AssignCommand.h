//
// Created by guy on 13/12/2019.
//

#ifndef FLIGHTGEAR_COMMANDS_ASSIGNCOMMAND_H_
#define FLIGHTGEAR_COMMANDS_ASSIGNCOMMAND_H_

#include "Command.h"
class AssignCommand : public Command {
 public:
  AssignCommand();
  ~AssignCommand() override;
  int execute(Data* data) override;

};
#endif //FLIGHTGEAR_COMMANDS_ASSIGNCOMMAND_H_
