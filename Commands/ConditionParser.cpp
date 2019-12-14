//
// Created by guy on 13/12/2019.
//

#include "ConditionParser.h"
ConditionParser::ConditionParser(int index) : Command(index) {}
int ConditionParser::execute() {
  //todo: implement ConditionParser::execute
  return Command::execute();
}
void ConditionParser::updateCondition() {
  //todo: implement ConditionParser::updateCondition
  _condition = false;
}
