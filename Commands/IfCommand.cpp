//
// Created by guy on 13/12/2019.
//

#include "IfCommand.h"
IfCommand::IfCommand(int index) : ConditionParser(index) {}
int IfCommand::execute() {
  //todo: implement IfCommand::execute
  updateCondition();
  if (_condition) {
    for (Command* c : _commandsList) {
      c->execute();
    }
  }
  return ConditionParser::execute();
}
