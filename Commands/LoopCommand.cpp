//
// Created by guy on 13/12/2019.
//

#include "LoopCommand.h"
LoopCommand::LoopCommand() = default;
LoopCommand::~LoopCommand() = default;
int LoopCommand::execute(Data* data) {
  //set _start and _end
  setStart(_index + 5);
  int temp = _index;
  while (data->getTextArr()[temp] != "}") { temp++; }
  setEnd(temp - 1);

  //updating condition before entering loop
  updateCondition(data);
  while (_condition) {
    //executing all commands inside the scope, the same way parser does
    int index = _start;
    while (index < _end) {
      Command* c;
      c = data->getCommandTable().at(data->getTextArr()[index]);
      if (c != nullptr) {
        c->setIndex(index);
        index += c->execute(data);
      }
    }
    //updating condition before entering next iteration
    updateCondition(data);
  }
  return 6 + (_end - _start + 1);
}
