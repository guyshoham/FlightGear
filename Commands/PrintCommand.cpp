//
// Created by guy on 13/12/2019.
//
#include <iostream>
#include <sstream>
#include "PrintCommand.h"
#include "../Expressions/Expression.h"
#include "../Expressions/Calculator.h"

PrintCommand::PrintCommand() = default;
int PrintCommand::execute(string* textArr,
                          unordered_map<string, Command*>& commandTable,
                          unordered_map<string, VarInfo*>& symTable) {

  string value = textArr[_index + 1];

  //checks if the argument is a string or not
  if (value.at(0) == '\"') {
    cout << value << endl;
  } else {
    auto* interpreter = new Interpreter();
    Expression* expression = nullptr;

    for (pair<std::string, VarInfo*> element : symTable) {
      ostringstream temp;
      temp << element.second->getValue();
      string valueStr = temp.str();
      interpreter->setVariables(element.second->getName() + "=" + valueStr);
    }

    expression = interpreter->interpret(value);
    cout << expression->calculate() << endl;
    delete expression;
    delete interpreter;
  }

  return 2;
}
