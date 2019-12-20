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
  unordered_map<string, VarInfo*> symTableUser;
  unordered_map<string, VarInfo*> symTableSimulator;
  ~Data() = default;
  Data() = default;
  void addCommand(string key, Command* value) {
    commandTable[key] = value;
  }

  void addVariable(string key, string name, bool direction, string path) {
    auto* v = new VarInfo(name, direction, path);
    symTableUser[key] = v;
  }

  void addVariable(string key, bool direction, string path) {
    auto* v = new VarInfo(key, direction, path);
    symTableSimulator[key] = v;
  }

};

#endif //MILSTONE1__DATA_H_
