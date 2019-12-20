//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_CONNECTCOMMAND_H_

#include "Command.h"

#define MILSTONE1_COMMANDS_CONNECTCOMMAND_H_

class ConnectCommand : public Command {
public:
    ConnectCommand();

    int execute(string *textArr,
                unordered_map<string, Command *> &commandTable,
                unordered_map<string, VarInfo *> &symTable) override;

    static void openClientServer(const char *ip,int port);

};

#endif //MILSTONE1_COMMANDS_CONNECTCOMMAND_H_
