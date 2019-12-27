#ifndef EX1__EX1_H_
#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include <typeinfo>
#include "Expression.h"

using namespace std;
#define EX1__EX1_H_

class Value : public Expression {

  const double _value;

 public:
  Value(double value);
  double calculate();
  virtual string getType();

};

class Variable : public Expression {
  string _name;

  double _value;

 public:
  Variable(string name, double value);
  double calculate();
  Variable& operator++();
  Variable& operator--();
  Variable& operator+=(double num);
  Variable& operator-=(double num);
  Variable& operator++(int);
  Variable& operator--(int);
  virtual string getType();
  string getName();
  double getValue();
  void setValue(double value);

};

class BinaryOperator : public Expression {
 protected:
  Expression* _left, * _right;

 public:
  BinaryOperator(Expression* left, Expression* right);
  virtual ~BinaryOperator();
};

class UnaryOperator : public Expression {
 protected:
  Expression* _expression;

 public:
  UnaryOperator(Expression* expression);
  virtual ~UnaryOperator();
};

class Plus : public BinaryOperator {

 public:
  Plus(Expression* left, Expression* right);
  double calculate();
  virtual ~Plus();
  virtual string getType();

};

class Minus : public BinaryOperator {

 public:
  Minus(Expression* left, Expression* right);
  double calculate();
  virtual ~Minus();
  virtual string getType();

};

class Mul : public BinaryOperator {

 public:
  Mul(Expression* left, Expression* right);
  double calculate();
  virtual ~Mul();
  virtual string getType();

};

class Div : public BinaryOperator {

 public:
  Div(Expression* left, Expression* right);
  double calculate();
  virtual string getType();
  virtual ~Div();
};

class UPlus : public UnaryOperator {

 public:
  UPlus(Expression* expression);
  double calculate();
  virtual ~UPlus();
  virtual string getType();

};

class UMinus : public UnaryOperator {

 public:
  UMinus(Expression* expression);
  double calculate();
  virtual ~UMinus();
  virtual string getType();

};

class Interpreter {
  Variable* _variables[10] = {nullptr};

 public:
  Interpreter();
  Expression* interpret(string input);
  void setVariables(string input);
  virtual ~Interpreter();
  static bool isOperand(const char& c);
  static bool isOperator(const char& c);
  static bool hasHigherPrec(const char& top, const char& c);
  static bool isOpeningParentheses(const char c);
  static bool isClosingParentheses(const char c);
  void addToArr(Variable* variable);
  static void replaceAll(string& str, const string& from, const string& to);
  static Value* getWholeValue(string input, int pos, int* posAfter);
  static Expression* createExpressionFromStack(stack<char>* stack);
  queue<Expression*> infixToPostfix(string input);
  static Expression* integrateExpressions(queue<Expression*> output);
  static bool validateMathExpression(const string expression);
  static bool validateVariableExpression(const string expression, const char symbol);
  static bool validateVariableName(const string name);
  static bool validateVariableValue(const string value);
};

#endif //EX1__EX1_H_
