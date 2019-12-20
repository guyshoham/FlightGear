//
// Created by guy on 13/12/2019.
//

#include "LoopCommand.h"
LoopCommand::LoopCommand() = default;
int LoopCommand::execute(string* textArr,
                         unordered_map<string, Command*>& commandTable,
                         unordered_map<string, VarInfo*>& symTable) {
  //todo: implement LoopCommand::execute

  //set _start and _end
  setStart(_index + 5);
  int temp = _index;
  while (textArr[temp] != "}") {
    temp++;
  }
  setEnd(temp - 1);

  updateCondition(textArr, symTable);
  while (_condition) {
    int index = _start;
    while (index < _end) {
      Command* c;
      c = commandTable.at(textArr[index]);
      if (c != nullptr) {
        c->setIndex(index);
        index += c->execute(textArr, commandTable, symTable);
      }
    }
    updateCondition(textArr, symTable);
  }
  return 5 + (_end - _start + 1);
}
