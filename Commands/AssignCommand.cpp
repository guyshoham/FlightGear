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
int AssignCommand::execute(Data* data) {
  string key = data->getTextArr()[_index];
  string value = data->getTextArr()[_index + 2];

  auto* interpreter = new Interpreter();
  Expression* expression = nullptr;

  //setting variables for interpreter
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
    double newValue = expression->calculate();
    //getting the VarInfo and updating value
    VarInfo* v = data->getSymTableUser().at(key);
    v->setValue(newValue);
    if (v->getDirection() == 1) {
      ostringstream temp;
      temp << v->getValue();
      string valueToSend = temp.str();
      string path = v->getPath();
      string commandToSend = "setd " + path + " " + valueToSend + "\r\n";

      //pushing command string to Data queue
      char* msg = new char[commandToSend.size() + 1];
      copy(commandToSend.begin(), commandToSend.end(), msg);
      msg[commandToSend.size()] = '\0';
      data->getCommandsToSimulator().push(msg);
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
