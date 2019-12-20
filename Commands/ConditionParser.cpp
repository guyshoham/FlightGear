//
// Created by guy on 13/12/2019.
//

#include <sstream>
#include "ConditionParser.h"
#include "../Expressions/Expression.h"
#include "../Expressions/Calculator.h"

ConditionParser::ConditionParser() { _condition = false; }

//todo: implement ConditionParser::execute
int ConditionParser::execute(string* textArr,
                             unordered_map<string, Command*>& commandTable,
                             unordered_map<string, VarInfo*>& symTable) { return _commandsList.size() + 1; }

//todo: implement ConditionParser::updateCondition
void ConditionParser::updateCondition(string* textArr, unordered_map<string, VarInfo*>& symTable) {

  string leftStr = textArr[_index + 1];
  string symbol = textArr[_index + 2];
  string rightStr = textArr[_index + 3];

  auto* interpreter = new Interpreter();
  Expression* left = nullptr;
  Expression* right = nullptr;

  //set variables
  for (pair<string, VarInfo*> element : symTable) {
    ostringstream temp;
    temp << element.second->getValue();
    string valueStr = temp.str();
    interpreter->setVariables(element.second->getName() + "=" + valueStr);
  }

  left = interpreter->interpret(leftStr);
  right = interpreter->interpret(rightStr);

  double leftValue = left->calculate();
  double rightValue = right->calculate();

  if (symbol == "<") _condition = leftValue < rightValue;
  else if (symbol == ">") _condition = leftValue > rightValue;
  else if (symbol == "<=") _condition = leftValue <= rightValue;
  else if (symbol == ">=") _condition = leftValue >= rightValue;
  else if (symbol == "==") _condition = leftValue == rightValue;

}
void ConditionParser::setStart(int index) { _start = index; }
void ConditionParser::setEnd(int index) { _end = index; }
