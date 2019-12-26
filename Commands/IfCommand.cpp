//
// Created by guy on 13/12/2019.
//

#include "IfCommand.h"
IfCommand::IfCommand() = default;
int IfCommand::execute(string* textArr,
                       unordered_map<string, Command*>& commandTable,
                       unordered_map<string, VarInfo*>& symTableUser,
                       unordered_map<string, VarInfo*>& symTableSimulator,
                       queue<const char*>&  commandsToSimulator) {
  //set _start and _end
  setStart(_index + 5);
  int temp = _index;
  while (textArr[temp] != "}") {
    temp++;
  }
  setEnd(temp - 1);

  updateCondition(textArr, symTableUser);
  if (_condition) {
    int index = _start;
    while (index < _end) {
      Command* c;
      c = commandTable.at(textArr[index]);
      if (c != nullptr) {
        c->setIndex(index);
        index += c->execute(textArr, commandTable, symTableUser, symTableSimulator, commandsToSimulator);
      }
    }
  }
  return 6 + (_end - _start + 1);
}
