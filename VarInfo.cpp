//
// Created by guy on 16/12/2019.
//

#include "VarInfo.h"

VarInfo::VarInfo(string name, int direction, string path) {
  _name = name;
  _direction = direction;
  _path = path;
  _value = 0.0;
}
double VarInfo::getValue() {
  lock_guard<mutex> lock(m_lock);
  return _value;
}
void VarInfo::setValue(double value) {
  lock_guard<mutex> lock(m_lock);
  _value = value;
}
string VarInfo::getName() {
  lock_guard<mutex> lock(m_lock);
  return _name;
}
string VarInfo::getPath() {
  lock_guard<mutex> lock(m_lock);
  return _path;
}
int VarInfo::getDirection() {
  lock_guard<mutex> lock(m_lock);
  return _direction;
}
void VarInfo::setDirection(int direction) {
  lock_guard<mutex> lock(m_lock);
  _direction = direction;
}
void VarInfo::setSecondName(string secondName) {
  lock_guard<mutex> lock(m_lock);
  _secondName = secondName;
}
string VarInfo::getSecondName() {
  lock_guard<mutex> lock(m_lock);
  return _secondName;
}
