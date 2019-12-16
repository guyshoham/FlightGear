//
// Created by guy on 13/12/2019.
//

#ifndef MILSTONE1_COMMANDS_COMMAND_H_
#define MILSTONE1_COMMANDS_COMMAND_H_

class Command {
 private:
  int _index;
 public:
  Command();
  virtual int execute() = 0;
  virtual void setIndex(int index);
  virtual ~Command();
};

#endif //MILSTONE1_COMMANDS_COMMAND_H_
