//
// Created by guy on 16/12/2019.
//

#include "VarInfo.h"

VarInfo::VarInfo(string name, string direction, string sim) {
  _name = name;
  _direction = direction;
  _path = sim;
  _value = 0.0;
}
double VarInfo::getValue() {
  return _value;
}
void VarInfo::setValue(double value) {
  _value = value;
}
string VarInfo::getName() {
  return _name;
}
string VarInfo::getPath() {
  return _path;
}
string VarInfo::getDirection() {
  return _direction;
}
