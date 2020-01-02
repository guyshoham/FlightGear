//
// Created by guy on 13/12/2019.
//

#include <iostream>
#include <sstream>
#include "AssignCommand.h"
#include "../Expressions/Expression.h"
#include "../Expressions/Calculator.h"

AssignCommand::AssignCommand() = default;
AssignCommand::~AssignCommand() = default;
int AssignCommand::execute(string* textArr,
                           unordered_map<string, Command*>& commandTable,
                           unordered_map<string, VarInfo*>& symTableUser,
                           unordered_map<string, VarInfo*>& symTableSimulator,
                           queue<const char*>& commandsToSimulator) {
  commandTable = commandTable;
  symTableSimulator = symTableSimulator;

  string key = textArr[_index];
  string value = textArr[_index + 2];

  auto* interpreter = new Interpreter();
  Expression* expression = nullptr;

  for (pair<string, VarInfo*> element : symTableUser) {
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
    double newValue = expression->calculate();
    VarInfo* v = symTableUser.at(key);
    v->setValue(newValue);
    if (v->getDirection() == 1) {
      ostringstream temp;
      temp << v->getValue();
      string valueToSend = temp.str();
      string path = v->getPath();
      //path.erase(0, 1);
      string commandToSend = "setd " + path + " " + valueToSend + "\r\n";

      //update simulator - send 'commandToSend'
      char* msg = new char[commandToSend.size() + 1];
      copy(commandToSend.begin(), commandToSend.end(), msg);
      msg[commandToSend.size()] = '\0';
      commandsToSimulator.push(msg);
    }
    delete expression;
    delete interpreter;
  } catch (const char* message) {
    cout << message << endl;
    delete expression;
    delete interpreter;
  }
  return 3;
}
