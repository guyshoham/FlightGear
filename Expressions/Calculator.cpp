//
// Created by Tsand on 11/10/2019.
//

#include "Calculator.h"
#include <stack>

Value::Value(double value1) : value(value1) {
}

Value::~Value() = default;

double Value::calculate() {
  return value;
}

Variable::Variable(string name1, double value1) {
  name = name1;
  value = value1;
}

Variable::~Variable() = default;

double Variable::calculate() {
  return value;
}

string Variable::getName() {
  return this->name;
}

double Variable::getValue() {
  return this->value;
}

Variable& Variable::operator++() {
  this->value++;
  return *this;
}

Variable& Variable::operator--() {
  this->value--;
  return *this;
}

Variable& Variable::operator+=(double e) {
  this->value += e;
  return *this;
}

Variable& Variable::operator-=(double e) {
  this->value -= e;
  return *this;
}

Variable& Variable::operator++(int e) {
  this->value++;
  return *this;
}

Variable& Variable::operator--(int e) {
  this->value--;
  return *this;
}

UnaryOperator::UnaryOperator(Expression* expression1) {
  expression = expression1;
}

UnaryOperator::~UnaryOperator() {
  delete this->expression;
}

double UnaryOperator::calculate() {
  return expression->calculate();
}

UPlus::UPlus(Expression* expression1) : UnaryOperator(expression1) {
  expression = expression1;
}

UPlus::~UPlus() = default;

double UPlus::calculate() {
  return expression->calculate();
}

UMinus::UMinus(Expression* expression1) : UnaryOperator(expression1) {
  expression = expression1;
}

UMinus::~UMinus() = default;

double UMinus::calculate() {
  return -1 * expression->calculate();
}

BinaryOperator::BinaryOperator(Expression* rValue, Expression* lValue) {
  right = rValue;
  left = lValue;
}

BinaryOperator::~BinaryOperator() {
  delete this->right;
  delete this->left;
}

double BinaryOperator::calculate() {
  return right->calculate() + left->calculate();
}

Plus::Plus(Expression* rValue, Expression* lValue) : BinaryOperator(rValue, lValue) {
  right = rValue;
  left = lValue;
}

Plus::~Plus() = default;

double Plus::calculate() {
  return right->calculate() + left->calculate();
}

Minus::Minus(Expression* rValue, Expression* lValue) : BinaryOperator(rValue, lValue) {
  right = rValue;
  left = lValue;
}

Minus::~Minus() = default;

double Minus::calculate() {
  return right->calculate() - left->calculate();
}

Mul::Mul(Expression* rValue, Expression* lValue) : BinaryOperator(rValue, lValue) {
  right = rValue;
  left = lValue;
}

Mul::~Mul() = default;

double Mul::calculate() {
  return right->calculate() * left->calculate();
}

Div::Div(Expression* rValue, Expression* lValue) : BinaryOperator(rValue, lValue) {
  right = rValue;
  left = lValue;
}

Div::~Div() = default;

double Div::calculate() {
  if (right->calculate() == 0) {
    throw "division by zero";
  }
  return left->calculate() / right->calculate();
}

Interpreter::Interpreter() {
  size = 0;
}

Interpreter::~Interpreter() {
  for (int i = 0; i < size; i++) {
    delete variables[i];
  }
}

void Interpreter::setVariables(string expression) {
  int pos, numDelimiter = 0;
  string test = expression, name;
  double value;
  char delimiter = ';';
  while ((pos = test.find(delimiter)) != string::npos) {
    numDelimiter++;
    test.erase(0, pos + 1);
  }
  string variablesStrings[numDelimiter + 1];

  if (numDelimiter > 0) {
    for (int i = 0; i < numDelimiter + 1; i++) {
      variablesStrings[i] = expression.substr(0, expression.find(delimiter));
      expression.erase(0, expression.find(delimiter) + 1);
    }
  }
  variablesStrings[numDelimiter] = expression;

  for (int i = 0; i < numDelimiter + 1; i++) {
    string currentVar = variablesStrings[i];
    pos = currentVar.find('=');
    name = currentVar.substr(0, pos);
    try {
      value = stod(variablesStrings[i].substr(pos + 1, variablesStrings[i].length() - 1));
    } catch (...) {
      throw "illegal variable assignment!";
    }
    this->variables[this->size] = new Variable(name, value);
    this->size++;
  }

}

string Interpreter::switchVariables(string expression) {
  string delimiter, strValue;
  double value;
  int pos = -1;
  for (int i = this->size - 1; i >= 0; i--) {
    delimiter = this->variables[i]->getName();
    value = this->variables[i]->getValue();
    strValue = to_string(value);
    //strValue = strValue.substr(0, strValue.find('0'));
    if ((pos = expression.find(delimiter)) != -1) {
      expression.replace(pos, delimiter.length(), strValue);
    }
  }

  for (int i = 0; i < expression.length(); i++) {
    if ((expression[i] >= 'a' && expression[i <= 'z']) || (expression[i] >= 'A' && expression[i] <= 'Z')) {
      throw "illegal math expression";
    }
    if (IsOperator(expression[i]) && i < expression.length() - 1 && IsOperator(expression[i + 1])) {
      throw "illegal math expression";
    }
  }

  return expression;
}

Expression* Interpreter::interpret(string expression) {
  expression = switchVariables(expression);
  int lastDigit = 0;
  stack<char> stack1;
  string postfix = "", num;
  for (int i = 0; i < expression.length(); i++) {
    if (IsOperand(expression[i])) {
      lastDigit = findLastDigit(i, expression);
      num = expression.substr(i, lastDigit - i);
      postfix += num;
      postfix += '|';
      i = lastDigit - 1;
    } else if (IsOperator(expression[i])) {

      while (!stack1.empty() && stack1.top() != '(' && HasHigherPrecedence(stack1.top(), expression[i])) {

        postfix += stack1.top();
        stack1.pop();
      }
      if (expression[i] == '-' && (i == 0 || (!stack1.empty() && stack1.top() == '('))) {
        stack1.push('$');
      }
      stack1.push(expression[i]);
    } else if (expression[i] == '(') {
      stack1.push(expression[i]);
    } else if (expression[i] == ')') {
      while (!stack1.empty() && stack1.top() != '(') {
        postfix += stack1.top();
        if (stack1.top() == '$') {
          postfix += '$';
        }
        stack1.pop();
      }
      stack1.pop();
    }
  }
  if (!stack1.empty()) {
    postfix += stack1.top();
    stack1.pop();
    if (!stack1.empty() && stack1.top() == '$') {
      postfix += '$';
    }
  }
  stack<Expression*> s;
  Expression* first = nullptr, * last = nullptr;
  for (int i = 0; i < postfix.length(); i++) {
    if (IsOperand(postfix[i])) {
      lastDigit = postfix.find('|', i);
      s.push(new Value(stod(postfix.substr(i, lastDigit))));
      i = lastDigit;
    }
    if (IsOperator(postfix[i])) {
      if (s.size() >= 2) {
        first = s.top();
        s.pop();
        last = s.top();
        s.pop();
        if (postfix[i] == '+') {
          s.push(new Plus(first, last));
        }
        if (postfix[i] == '-') {
          if (postfix[i + 1] == '$') {
            s.push(last);
            s.push(new UMinus(first));
          } else {
            s.push(new Minus(last, first));
          }
        }
        if (postfix[i] == '*') {
          s.push(new Mul(first, last));
        }
        if (postfix[i] == '/') {
          s.push(new Div(first, last));
        }
      } else {
        s.push(new UMinus(s.top()));
      }
    }
  }
  Expression* expression1 = s.top();
  while (!s.empty()) {
    s.pop();
  }
  return expression1;
}

int Interpreter::findLastDigit(int i, string expression) {
  for (i; i < expression.length(); i++) {
    if (!IsOperand(expression[i])) {
      if (expression[i] != '.') {
        return i;
      }

    }
  }
  return i;
}

int Interpreter::GetOperatorWeight(char op) {
  int weight = -1;
  switch (op) {
    case '+':weight = 1;
      break;
    case '-':weight = 1;
      break;
    case '*':weight = 2;
      break;
    case '/':weight = 2;
      break;
    default:break;
  }
  return weight;
}

int Interpreter::HasHigherPrecedence(char operator1, char operator2) {
  int op1 = GetOperatorWeight(op1);
  int op2 = GetOperatorWeight(op2);
  return op1 < op2;
}

bool Interpreter::IsOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

bool Interpreter::IsOperand(char C) {
  if (C >= '0' && C <= '9') return true;
  if (C >= 'a' && C <= 'z') return true;
  return C >= 'A' && C <= 'Z';
}


