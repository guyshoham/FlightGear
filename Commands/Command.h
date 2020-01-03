//
// Created by guy on 13/12/2019.
//

#ifndef FLIGHTGEAR_COMMANDS_COMMAND_H_
#include <string>
#include <unordered_map>
#include <queue>
#include "../Data.h"
#define FLIGHTGEAR_COMMANDS_COMMAND_H_

using namespace std;

class Command {
 protected:
  int _index;
 public:
  Command();
  virtual int execute(Data* data) = 0;
  virtual void setIndex(int index);
  virtual ~Command();
};

#endif //FLIGHTGEAR_COMMANDS_COMMAND_H_
