//
// Created by guy on 13/12/2019.
//

#include "AssignCommand.h"

AssignCommand::AssignCommand() = default;
int AssignCommand::execute(string* textArr,
                           unordered_map<string, Command*>& commandTable,
                           unordered_map<string, VarInfo*>& symTable) {
  //todo: implement AssignCommand::execute

  //todo: add expressions classes and use here

  //todo: update new value in simulator

  string key = textArr[_index];

  //in case value type is double (not an expression)
  double newValue = stod(textArr[_index + 1]);
  symTable.at(key)->setValue(newValue);

  return 3;
}
