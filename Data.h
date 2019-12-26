//
// Created by guy on 16/12/2019.
//

#ifndef FLIGHTGEAR__DATA_H_
#include <unordered_map>
#include <mutex>
#include <queue>
#include <string>
#include "Commands/Command.h"
#include "VarInfo.h"
#define FLIGHTGEAR__DATA_H_

using namespace std;

class Data {
 public:
  mutex m;
  string* textArr;
  int arrSize;
  unordered_map<string, Command*> commandTable;
  unordered_map<string, VarInfo*> symTableUser;
  unordered_map<string, VarInfo*> symTableSimulator;
  queue<const char*> commandsToSimulator;
  ~Data() = default;
  Data() = default;
  void addCommand(string key, Command* value) {
    lock_guard<std::mutex> lock(m);
    commandTable[key] = value;
  }

  void addVariable(string key, string name, bool direction, string path) {
    lock_guard<mutex> lock(m);
    auto* v = new VarInfo(name, direction, path);
    symTableUser[key] = v;
  }

  void addVariable(string key, bool direction, string path) {
    lock_guard<std::mutex> lock(m);
    auto* v = new VarInfo(key, direction, path);
    symTableSimulator[key] = v;
  }

};

#endif //FLIGHTGEAR__DATA_H_
