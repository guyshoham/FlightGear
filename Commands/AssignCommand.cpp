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
                           unordered_map<string, VarInfo*>& symTableUser,
                           unordered_map<string, VarInfo*>& symTableSimulator,
                           queue<const char*>& commandsToSimulator) {

  string key = textArr[_index];
  string value = textArr[_index + 2];

  auto* interpreter = new Interpreter();
  Expression* expression = nullptr;

  for (pair<string, VarInfo*> element : symTableUser) {
    ostringstream temp;
    temp << element.second->getValue();
    string valueStr = temp.str();
    interpreter->setVariables(element.second->getName() + "=" + valueStr);
  }

  expression = interpreter->interpret(value);

  double newValue = expression->calculate();
  VarInfo* v = symTableUser.at(key);
  v->setValue(newValue);

  delete expression;
  delete interpreter;

  if (v->getDirection() == 1) {
    ostringstream temp;
    temp << v->getValue();
    string valueToSend = temp.str();
    string commandToSend = "set " + v->getPath() + " " + valueToSend;
    cout << commandToSend << endl;
    //todo: update simulator - send 'commandToSend'
    char* msg = new char[commandToSend.size() + 1];
    copy(commandToSend.begin(), commandToSend.end(), msg);
    msg[commandToSend.size()] = '\0';
    commandsToSimulator.push(msg);
  }

  return 3;
}
