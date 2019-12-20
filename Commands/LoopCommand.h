//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_LOOPCOMMAND_H_
#define MILSTONE1_COMMANDS_LOOPCOMMAND_H_

#include "ConditionParser.h"
class LoopCommand : public ConditionParser {
 public:
  LoopCommand();
  int execute(string* textArr,
              unordered_map<string, Command*>& commandTable,
              unordered_map<string, VarInfo*>& symTableTable,
              unordered_map<string, VarInfo*>& symTableSimulator) override;
};
#endif //MILSTONE1_COMMANDS_LOOPCOMMAND_H_
