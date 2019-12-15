//
// Created by guy on 13/12/2019.
//

#include "IfCommand.h"
IfCommand::IfCommand() = default;
int IfCommand::execute() {
  //todo: implement IfCommand::execute
  updateCondition();
  if (_condition) {
    for (Command* c : _commandsList) {
      c->execute();
    }
  }
  return _commandsList.size() + 1;
}
