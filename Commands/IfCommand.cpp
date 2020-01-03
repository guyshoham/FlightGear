//
// Created by guy on 13/12/2019.
//

#include "IfCommand.h"
IfCommand::IfCommand() = default;
IfCommand::~IfCommand() = default;
int IfCommand::execute(Data* data) {
  //set _start and _end
  setStart(_index + 5);
  int temp = _index;
  while (data->getTextArr()[temp] != "}") {
    temp++;
  }
  setEnd(temp - 1);

  updateCondition(data);
  if (_condition) {
    int index = _start;
    while (index < _end) {
      Command* c;
      c = data->getCommandTable().at(data->getTextArr()[index]);
      if (c != nullptr) {
        c->setIndex(index);
        index += c->execute(data);
      }
    }
  }
  return 6 + (_end - _start + 1);
}
