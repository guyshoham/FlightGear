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
  static Data* _instance;
  mutex m;
  string* textArr;
  int arrSize;
  unordered_map<string, Command*> commandTable;
  unordered_map<string, VarInfo*> symTableUser;
  unordered_map<string, VarInfo*> symTableSimulator;
  queue<const char*> commandsToSimulator;

  Data() = default;
  ~Data() = default;

 public:
  static Data* getInstance() {
    if (_instance == nullptr) {
      _instance = new Data();
    }
    return _instance;
  }
  string* getTextArr() { return textArr; }
  void setTextArr(string* arr) { textArr = arr; }
  int getArrSize() { return arrSize; }
  void setArrSize(int size) { arrSize = size; }
  unordered_map<string, Command*>& getCommandTable() { return commandTable; }
  unordered_map<string, VarInfo*>& getSymTableUser() { return symTableUser; }
  unordered_map<string, VarInfo*>& getSymTableSimulator() { return symTableSimulator; }
  queue<const char*>& getCommandsToSimulator() { return commandsToSimulator; }
  void addCommand(string key, Command* value) {
    lock_guard<std::mutex> lock(m);
    commandTable[key] = value;
  }
  void addVariable(string key, bool direction, string path) {
    lock_guard<std::mutex> lock(m);
    auto* v = new VarInfo(key, direction, path);
    symTableSimulator[key] = v;
  }
};

#endif //FLIGHTGEAR__DATA_H_
