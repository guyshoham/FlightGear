//
// Created by guy on 13/12/2019.
//

#include "LoopCommand.h"
LoopCommand::LoopCommand() = default;
int LoopCommand::execute(string* textArr,
                         unordered_map<string, Command*>& commandTable,
                         unordered_map<string, VarInfo*>& symTable) {
  //todo: implement LoopCommand::execute
  updateCondition(textArr, symTable);
  while (_condition) {
    for (Command* c : _commandsList) {
      c->execute(textArr, commandTable, symTable);
    }
    updateCondition(textArr, symTable);
  }
  return _commandsList.size() + 1;
}
