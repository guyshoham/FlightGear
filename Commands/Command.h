//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_COMMAND_H_
#include <string>
#include <unordered_map>
#include "../VarInfo.h"
#define MILSTONE1_COMMANDS_COMMAND_H_

using namespace std;

class Command {
 protected:
  int _index;
 public:
  Command();
  virtual int execute(string* textArr,
                      unordered_map<string, Command*>& commandTable,
                      unordered_map<string, VarInfo*>& symTable) = 0;
  virtual void setIndex(int index);
  virtual ~Command();
};

#endif //MILSTONE1_COMMANDS_COMMAND_H_
