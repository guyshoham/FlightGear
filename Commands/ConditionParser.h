//
// Created by guy on 13/12/2019.
//

#ifndef FLIGHTGEAR_COMMANDS_CONDITIONPARSER_H_
#include <list>
#include "Command.h"
#define FLIGHTGEAR_COMMANDS_CONDITIONPARSER_H_

using namespace std;
class ConditionParser : public Command {
 protected:
  bool _condition;
  int _start, _end; //start and end indexes, represent sub-array of commands inside '{}'
 public:
  ConditionParser();
  int execute(string* textArr,
              unordered_map<string, Command*>& commandTable,
              unordered_map<string, VarInfo*>& symTableUser,
              unordered_map<string, VarInfo*>& symTableSimulator,
              queue<const char*>  commandsToSimulator) override;
  virtual void updateCondition(string* textArr, unordered_map<string, VarInfo*>& symTableUser);
  virtual void setStart(int index);
  virtual void setEnd(int index);
};
#endif //FLIGHTGEAR_COMMANDS_CONDITIONPARSER_H_
