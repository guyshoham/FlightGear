//
// Created by guy on 16/12/2019.
//

#ifndef MILSTONE1__DATA_H_
#include <unordered_map>
#include <string>
#include "Commands/Command.h"
#include "VarInfo.h"
#define MILSTONE1__DATA_H_

using namespace std;

class Data {
 public:
  string* textArr;
  int arrSize;
  unordered_map<string, Command*> commandTable;
  unordered_map<string, VarInfo*> symTable;
  ~Data() = default;
  Data() = default;
  void addCommand(string key, Command* value) {
    commandTable[key] = value;
  }

};

#endif //MILSTONE1__DATA_H_
