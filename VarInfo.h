//
// Created by guy on 16/12/2019.
//

#ifndef MILSTONE1__VARINFO_H_
#include <string>
#define MILSTONE1__VARINFO_H_

using namespace std;

class VarInfo {
  string _name, _secondName, _path;
  int _direction;
  // "<-": 0
  // "->": 1
  // "=": 2
  double _value;

 public:
  VarInfo(string name, int direction, string sim);
  double getValue();
  void setValue(double value);
  string getSecondName();
  void setSecondName(string secondName);
  string getName();
  int getDirection();
  void setDirection(int direction);
  string getPath();

};

#endif //MILSTONE1__VARINFO_H_
