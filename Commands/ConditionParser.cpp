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
ConditionParser::~ConditionParser() = default;
int ConditionParser::execute(Data* data) { return 6 + (_end - _start + 1); }
void ConditionParser::setStart(int index) { _start = index; }
void ConditionParser::setEnd(int index) { _end = index; }
void ConditionParser::updateCondition(Data* data) {
  string leftStr = data->getTextArr()[_index + 1];
  string symbol = data->getTextArr()[_index + 2];
  string rightStr = data->getTextArr()[_index + 3];

  auto* interpreter = new Interpreter();
  Expression* left = nullptr;
  Expression* right = nullptr;

  //setting variables for interpreter
  for (pair<string, VarInfo*> element : data->getSymTableUser()) {
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
    //calculating left and right expression
    left = interpreter->interpret(leftStr);
    right = interpreter->interpret(rightStr);
    double leftValue = left->calculate();
    double rightValue = right->calculate();

    //we round the values before checking the equality
    float leftRound = roundf(leftValue * 100) / 100;
    float rightRound = roundf(rightValue * 100) / 100;

    //updating _condition field
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
