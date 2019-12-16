//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_CONDITIONPARSER_H_
#include <list>
#include "Command.h"
#define MILSTONE1_COMMANDS_CONDITIONPARSER_H_

using namespace std;
class ConditionParser : public Command {
 protected:
  list<Command*> _commandsList;
  bool _condition;
 public:
  ConditionParser();
  int execute(string* textArr,
              unordered_map<string, Command*> commandTable,
              unordered_map<string, VarInfo*> symTable) override;
  virtual void updateCondition();
};
#endif //MILSTONE1_COMMANDS_CONDITIONPARSER_H_
