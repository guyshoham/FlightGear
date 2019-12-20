//
// Created by guy on 13/12/2019.
//

#include "IfCommand.h"
IfCommand::IfCommand() = default;
int IfCommand::execute(string* textArr,
                       unordered_map<string, Command*>& commandTable,
                       unordered_map<string, VarInfo*>& symTable) {
  //todo: implement IfCommand::execute
  updateCondition(textArr, symTable);
  if (_condition) {
    /*for (Command* c : _commandsList) {
      c->execute(textArr, commandTable, symTable);
    }*/
  }
  return 5 + (_end - _start + 1);
}
