//
// Created by guy on 16/12/2019.
//

#ifndef MILSTONE1__VARINFO_H_
#include <string>
#define MILSTONE1__VARINFO_H_

using namespace std;

class VarInfo {
  string _name, _path;
  bool _direction; //"<-": 0, "->": 1
  double _value;

 public:
  VarInfo(string name, bool direction, string sim);
  double getValue();
  void setValue(double value);
  string getName();
  bool getDirection();
  string getPath();

};

#endif //MILSTONE1__VARINFO_H_
