//
// Created by guy on 13/12/2019.
//

#include <string>
#include <sstream>
#include "AssignCommand.h"
#include "DefineVarCommand.h"
#include "../VarInfo.h"
#include "../Expressions/Expression.h"
#include "../Expressions/Calculator.h"
using namespace std;

DefineVarCommand::DefineVarCommand() = default;
DefineVarCommand::~DefineVarCommand() = default;
int DefineVarCommand::execute(Data* data) {
  string name = data->getTextArr()[_index + 1];
  string arrow = data->getTextArr()[_index + 2];

  if (data->getTextArr()[_index + 3] == "sim") { //if command using Sim function
    string path = data->getTextArr()[_index + 4];

    int direction;
    direction = arrow == "->" ? 1 : 0;
    auto* info = new VarInfo(name, direction, path);

    //adding variable to commandTable
    data->getCommandTable()[name] = new AssignCommand();

    //adding variable to symTableUser
    data->getSymTableUser()[name] = info;

    //iterating over symTableSimulator to find the "twin"
    for (pair<string, VarInfo*> element : data->getSymTableSimulator()) {
      if (path == element.second->getPath()) {
        //found twin. setting direction of twin
        element.second->setDirection(direction);

        //setting second name for both values
        element.second->setSecondName(name);
        data->getSymTableUser()[name]->setSecondName(element.second->getName());
        break;
      }
    }
    return 5;
  } else {
    string value = data->getTextArr()[_index + 3];

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
      auto* info = new VarInfo(name, 2, "");
      info->setValue(expression->calculate());
      //adding variable to commandTable
      data->getCommandTable()[name] = new AssignCommand();
      //adding variable to symTableUser
      data->getSymTableUser()[name] = info;
      delete expression;
      delete interpreter;
    } catch (const char* message) {
      cout << message << endl;
      delete expression;
      delete interpreter;
    }
    return 4;
  }
}
