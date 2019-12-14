//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_CONDITIONPARSER_H_
#define MILSTONE1_COMMANDS_CONDITIONPARSER_H_

#include <list>
#include "Command.h"
using namespace std;
class ConditionParser : public Command {
 protected:
  list<Command*> _commandsList;
  bool _condition;
 public:
  ConditionParser(int index);
  int execute() override;
  virtual void updateCondition();
};
#endif //MILSTONE1_COMMANDS_CONDITIONPARSER_H_
