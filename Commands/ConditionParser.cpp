//
// Created by guy on 13/12/2019.
//

#include <sstream>
#include <math.h>
#include "ConditionParser.h"
#include "../Expressions/Expression.h"
#include "../Expressions/Calculator.h"

using namespace std;

ConditionParser::ConditionParser() { _condition = false; }

int ConditionParser::execute(string* textArr,
                             unordered_map<string, Command*>& commandTable,
                             unordered_map<string, VarInfo*>& symTableUser,
                             unordered_map<string, VarInfo*>& symTableSimulator,
                             queue<const char*>& commandsToSimulator) {
  textArr = textArr;
  commandTable = commandTable;
  symTableUser = symTableUser;
  symTableSimulator = symTableSimulator;
  commandsToSimulator = commandsToSimulator;
  return 5 + (_end - _start + 1);
}

void ConditionParser::updateCondition(string* textArr, unordered_map<string, VarInfo*>& symTableUser) {

  string leftStr = textArr[_index + 1];
  string symbol = textArr[_index + 2];
  string rightStr = textArr[_index + 3];

  auto* interpreter = new Interpreter();
  Expression* left = nullptr;
  Expression* right = nullptr;

  //set variables
  for (pair<string, VarInfo*> element : symTableUser) {
    ostringstream temp;
    temp << element.second->getValue();
    string valueStr = temp.str();
    if (leftStr.find(element.second->getName()) != string::npos
        || rightStr.find(element.second->getName()) != string::npos) {
      string variable = element.second->getName() + "=" + valueStr;
      interpreter->setVariables(variable);
    }
  }

  try {
    left = interpreter->interpret(leftStr);
    right = interpreter->interpret(rightStr);
    double leftValue = left->calculate();
    double rightValue = right->calculate();

    float leftRound = roundf(leftValue * 100) / 100;
    float rightRound = roundf(rightValue * 100) / 100;

    if (symbol == "<") _condition = leftRound < rightRound;
    else if (symbol == ">") _condition = leftRound > rightRound;
    else if (symbol == "<=") _condition = leftRound <= rightRound;
    else if (symbol == ">=") _condition = leftRound >= rightRound;
    else if (symbol == "==") _condition = leftRound == rightRound;
    delete left;
    delete right;
    delete interpreter;
  } catch (const char* message) {
    cout << message << endl;
    delete left;
    delete right;
    delete interpreter;
  }
}
void ConditionParser::setStart(int index) { _start = index; }
void ConditionParser::setEnd(int index) { _end = index; }
