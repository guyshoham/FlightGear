//
// Created by guy on 13/12/2019.
//

#include "ConditionParser.h"

ConditionParser::ConditionParser() { _condition = false; };
int ConditionParser::execute(string* textArr,
                             unordered_map<string, Command*> commandTable,
                             unordered_map<string, VarInfo*> symTable) {
  //todo: implement ConditionParser::execute
  return _commandsList.size() + 1;
}
void ConditionParser::updateCondition() {
  //todo: implement ConditionParser::updateCondition
  _condition = false;
}
