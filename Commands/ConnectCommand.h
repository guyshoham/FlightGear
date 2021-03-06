//
// Created by guy on 13/12/2019.
//

#ifndef FLIGHTGEAR_COMMANDS_CONNECTCOMMAND_H_

#include "Command.h"

#define FLIGHTGEAR_COMMANDS_CONNECTCOMMAND_H_

class ConnectCommand : public Command {
 public:
  ConnectCommand();
  ~ConnectCommand() override;
  int execute(Data* data) override;
  void openClientServer(const char* ip, int port, queue<const char*>&  commandsToSimulator);
  static void runningClientServer(int client_socket, queue<const char*>&  commandsToSimulator);
};

#endif //FLIGHTGEAR_COMMANDS_CONNECTCOMMAND_H_
