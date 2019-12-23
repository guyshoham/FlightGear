//
// Created by guy on 13/12/2019.
//

#include <iostream>
#include <sstream>
#include <unistd.h>
#include "SleepCommand.h"
#include "../Expressions/Expression.h"
#include "../Expressions/Calculator.h"
SleepCommand::SleepCommand() = default;
int SleepCommand::execute(string* textArr,
                          unordered_map<string, Command*>& commandTable,
                          unordered_map<string, VarInfo*>& symTableUser,
                          unordered_map<string, VarInfo*>& symTableSimulator) {

  string value = textArr[_index + 1];

  //checks if the argument is a string or not
  if (value.at(0) == '\"') {
    usleep(stod(value) * 1000); // function is using microseconds (1 millisecond = 1000 microseconds)
  } else {
    auto* interpreter = new Interpreter();
    Expression* expression = nullptr;

    for (pair<std::string, VarInfo*> element : symTableUser) {
      ostringstream temp;
      temp << element.second->getValue();
      string valueStr = temp.str();
      interpreter->setVariables(element.second->getName() + "=" + valueStr);
    }

    expression = interpreter->interpret(value);
    usleep(expression->calculate() * 1000); // function is using microseconds (1 millisecond = 1000 microseconds)
    delete expression;
    delete interpreter;
  }

  return 2;
}
