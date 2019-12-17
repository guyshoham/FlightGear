//
// Created by guy on 13/12/2019.
//
#include <iostream>
#include "PrintCommand.h"

PrintCommand::PrintCommand() = default;
int PrintCommand::execute(string* textArr,
                          unordered_map<string, Command*> commandTable,
                          unordered_map<string, VarInfo*> symTable) {
  //todo: implement PrintCommand::execute

  string value = textArr[_index + 1];

  //checks if the argument is a string or not
  if (value.at(0) == '\"') {
    cout << value << endl;
  } else {
    //todo: value is a variable or an expression. need to implement
  }

  return 2;
}
