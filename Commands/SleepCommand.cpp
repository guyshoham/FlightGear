//
// Created by guy on 13/12/2019.
//

#include <sstream>
#include <thread>
#include <chrono>
#include "SleepCommand.h"
#include "../Expressions/Expression.h"
#include "../Expressions/Calculator.h"

SleepCommand::SleepCommand() = default;

int SleepCommand::execute(string* textArr,
                          unordered_map<string, Command*>& commandTable,
                          unordered_map<string, VarInfo*>& symTableUser,
                          unordered_map<string, VarInfo*>& symTableSimulator,
                          queue<const char*>& commandsToSimulator) {
  commandTable = commandTable;
  symTableUser = symTableUser;
  symTableSimulator = symTableSimulator;
  commandsToSimulator = commandsToSimulator;

  string value = textArr[_index + 1];

  //checks if the argument is a string or not
  if (value.at(0) == '\"') {
    int time = stoi(value);
    this_thread::sleep_for(chrono::milliseconds(time));
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
      this_thread::sleep_for(chrono::milliseconds((int) expression->calculate()));
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
