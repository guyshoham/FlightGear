//
// Created by guy on 16/12/2019.
//

#include "VarInfo.h"

VarInfo::VarInfo(string name, string sim) {
  _name = name;
  _sim = sim;
  _value = 0.0;
}
double VarInfo::getValue() {
  return _value;
}
string VarInfo::getName() {
  return _name;
}
string VarInfo::getSim() {
  return _sim;
}
