//
// Created by guy on 13/12/2019.
//

#include <sstream>
#include <unistd.h>
#include "SleepCommand.h"
#include "../Expressions/Expression.h"
#include "../Expressions/Calculator.h"

SleepCommand::SleepCommand() = default;

int SleepCommand::execute(string* textArr,
                          unordered_map<string, Command*>& commandTable,
                          unordered_map<string, VarInfo*>& symTableUser,
                          unordered_map<string, VarInfo*>& symTableSimulator,
                          queue<const char*>& commandsToSimulator) {

  string value = textArr[_index + 1];

  //checks if the argument is a string or not
  if (value.at(0) == '\"') {
    usleep(stod(value) * 1000); // function is using microseconds (1 millisecond = 1000 microseconds)
  } else {
    auto* interpreter = new Interpreter();
    Expression* expression = nullptr;
    ostringstream temp;

    string valueStr;
    for (pair<string, VarInfo*> element : symTableUser) {
      temp << element.second->getValue();
      valueStr = temp.str();
      temp.str("");
      temp.clear();
      if (value.find(element.second->getName()) != string::npos) {
        string variable = element.second->getName() + "=" + valueStr;
        interpreter->setVariables(variable);
      }
    }

    try {
      expression = interpreter->interpret(value);
      usleep(expression->calculate() * 1000); // function is using microseconds (1 millisecond = 1000 microseconds)
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
