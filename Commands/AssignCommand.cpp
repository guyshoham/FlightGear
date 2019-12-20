//
// Created by guy on 13/12/2019.
//

#include <iostream>
#include <sstream>
#include "AssignCommand.h"
#include "../Expressions/Expression.h"
#include "../Expressions/Calculator.h"

AssignCommand::AssignCommand() = default;
int AssignCommand::execute(string* textArr,
                           unordered_map<string, Command*>& commandTable,
                           unordered_map<string, VarInfo*>& symTable) {

  string key = textArr[_index];
  string value = textArr[_index + 1];

  auto* interpreter = new Interpreter();
  Expression* expression = nullptr;

  for (pair<string, VarInfo*> element : symTable) {
    ostringstream temp;
    temp << element.second->getValue();
    string valueStr = temp.str();
    interpreter->setVariables(element.second->getName() + "=" + valueStr);
  }

  expression = interpreter->interpret(value);

  double newValue = expression->calculate();
  symTable.at(key)->setValue(newValue);

  delete expression;
  delete interpreter;

  return 3;
}
