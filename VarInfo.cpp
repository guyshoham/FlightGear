//
// Created by guy on 16/12/2019.
//

#include "VarInfo.h"

VarInfo::VarInfo(string name, int direction, string sim) {
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
int VarInfo::getDirection() {
  return _direction;
}
void VarInfo::setDirection(int direction) {
  _direction = direction;
}
void VarInfo::setSecondName(string secondName) {
  _secondName = secondName;
}
string VarInfo::getSecondName() {
  return _secondName;
}
