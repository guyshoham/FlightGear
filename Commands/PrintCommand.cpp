//
// Created by guy on 13/12/2019.
//
#include <iostream>
#include <sstream>
#include "PrintCommand.h"
#include "../Expressions/Expression.h"
#include "../Expressions/Calculator.h"

PrintCommand::PrintCommand() = default;
PrintCommand::~PrintCommand() = default;
int PrintCommand::execute(Data* data) {
  string value = data->getTextArr()[_index + 1];

  //checks if the argument is a string or not
  if (value.at(0) == '\"') {
    cout << value << endl;
  } else {
    auto* interpreter = new Interpreter();
    Expression* expression = nullptr;

    for (pair<string, VarInfo*> element : data->getSymTableUser()) {
      ostringstream temp;
      temp << element.second->getValue();
      string valueStr = temp.str();
      if (value.find(element.second->getName()) != string::npos) {
        string variable = element.second->getName() + "=" + valueStr;
        interpreter->setVariables(variable);
      }
    }

    try {
      expression = interpreter->interpret(value);
      cout << expression->calculate() << endl;
      delete expression;
      delete interpreter;
    } catch (const char* message) {
      cout << message << endl;
      delete expression;
      delete interpreter;
    }
  }

  return 2;
}
