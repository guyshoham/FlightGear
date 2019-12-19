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
                              unordered_map<string, VarInfo*>& symTable) {
  //todo: implement DefineVarCommand::execute
  string name = textArr[_index + 1];
  string direction = textArr[_index + 2];
  string path = textArr[_index + 4];

  //todo: apply sim() on path, and put it in varInfo

  auto* info = new VarInfo(name, direction, path);

  //adding variable to commandTable
  commandTable[name] = new AssignCommand();

  //adding variable to symTable
  symTable[name] = info;

  return 5;
}
