//
// Created by guy on 13/12/2019.
//

#include "FuncCommand.h"
FuncCommand::FuncCommand(int index) : Command(index) {}
int FuncCommand::execute() {
  //todo: implement FuncCommand::execute
  for (Command* c : _commandsList) {
    c->execute();
  }
  return _commandsList.size() + 1;
}
