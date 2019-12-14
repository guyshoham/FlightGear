//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_COMMAND_H_
#define MILSTONE1_COMMANDS_COMMAND_H_

class Command {
 private:
  int _index;
 public:
  Command(int index);
  virtual int execute() = 0;
  virtual ~Command();
};

#endif //MILSTONE1_COMMANDS_COMMAND_H_
