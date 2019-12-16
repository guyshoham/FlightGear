//
// Created by guy on 16/12/2019.
//

#ifndef MILSTONE1__VARINFO_H_
#include <string>
#define MILSTONE1__VARINFO_H_

using namespace std;

class VarInfo {
  string _name, _path, _direction;
  double _value;

 public:
  VarInfo(string name, string direction, string sim);
  double getValue();
  string getName();
  string getDirection();
  string getPath();

};

#endif //MILSTONE1__VARINFO_H_
