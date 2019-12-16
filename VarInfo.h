//
// Created by guy on 16/12/2019.
//

#ifndef MILSTONE1__VARINFO_H_
#define MILSTONE1__VARINFO_H_

#include <string>
using namespace std;

class VarInfo {
  string _name, _sim;
  double _value;

 public:
  VarInfo(string name, string sim);
  double getValue();
  string getName();
  string getSim();

};

#endif //MILSTONE1__VARINFO_H_
