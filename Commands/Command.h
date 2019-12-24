//
// Created by guy on 13/12/2019.
//

#ifndef FLIGHTGEAR_COMMANDS_COMMAND_H_
#include <string>
#include <unordered_map>
#include <queue>
#include "../VarInfo.h"
#define FLIGHTGEAR_COMMANDS_COMMAND_H_

using namespace std;

class Command {
 protected:
  int _index;
 public:
  Command();
  virtual int execute(string* textArr,
                      unordered_map<string, Command*>& commandTable,
                      unordered_map<string, VarInfo*>& symTableUser,
                      unordered_map<string, VarInfo*>& symTableSimulator,
                      queue<const char*>  commandsToSimulator) = 0;
  virtual void setIndex(int index);
  virtual ~Command();
};

#endif //FLIGHTGEAR_COMMANDS_COMMAND_H_
