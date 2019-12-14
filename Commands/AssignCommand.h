//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_ASSIGNCOMMAND_H_
#define MILSTONE1_COMMANDS_ASSIGNCOMMAND_H_

#include "Command.h"
class AssignCommand : public Command {
 public:
  AssignCommand(int index);
  int execute() override;

};
#endif //MILSTONE1_COMMANDS_ASSIGNCOMMAND_H_
