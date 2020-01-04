//
// Created by guy on 16/12/2019.
//

#ifndef FLIGHTGEAR__VARINFO_H_
#include <string>
#include <mutex>
#define FLIGHTGEAR__VARINFO_H_

using namespace std;

class VarInfo {
  string _name, _secondName, _path;
  mutex m_lock;
  int _direction;
  /** direction values:
   * "<-": 0
   * "->": 1
   * "=": 2 **/
  double _value;

 public:
  VarInfo(string name, int direction, string path);
  double getValue();
  void setValue(double value);
  string getSecondName();
  void setSecondName(string secondName);
  string getName();
  int getDirection();
  void setDirection(int direction);
  string getPath();

};

#endif //FLIGHTGEAR__VARINFO_H_
