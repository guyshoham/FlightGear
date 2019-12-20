//
// Created by guy on 13/12/2019.
//

#include "DefineVarCommand.h"
#include "AssignCommand.h"
#include "../VarInfo.h"
#include <string>
using namespace std;

DefineVarCommand::DefineVarCommand() = default;
int DefineVarCommand::execute(string* textArr,
                              unordered_map<string, Command*>& commandTable,
                              unordered_map<string, VarInfo*>& symTableUser,
                              unordered_map<string, VarInfo*>& symTableSimulator) {
  string name = textArr[_index + 1];
  string arrow = textArr[_index + 2];
  string path = textArr[_index + 4];

  bool direction;
  direction = arrow == "->";
  auto* info = new VarInfo(name, direction, path);

  //adding variable to commandTable
  commandTable[name] = new AssignCommand();

  //adding variable to symTableUser
  symTableUser[name] = info;

  return 5;
}
