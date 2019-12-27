#include "Calculator.h"
#include "Expression.h"
#include <stack>
#include <queue>

/**BinaryOperator**/
BinaryOperator::BinaryOperator(Expression* left, Expression* right) : _left(left), _right(right) {}
BinaryOperator::~BinaryOperator() {
  delete _left;
  delete _right;
}

/**UnaryOperator**/
UnaryOperator::UnaryOperator(Expression* expression) : _expression(expression) {}
UnaryOperator::~UnaryOperator() { delete _expression; }

/**Plus**/
Plus::Plus(Expression* left, Expression* right) : BinaryOperator(left, right) {}
Plus::~Plus() = default;
double Plus::calculate() { return _left->calculate() + _right->calculate(); }
string Plus::getType() { return "plus"; }

/**Minus**/
Minus::Minus(Expression* left, Expression* right) : BinaryOperator(left, right) {}
Minus::~Minus() = default;
double Minus::calculate() { return _left->calculate() - _right->calculate(); }
string Minus::getType() { return "minus"; }

/**Mul**/
Mul::Mul(Expression* left, Expression* right) : BinaryOperator(left, right) {}
Mul::~Mul() = default;
double Mul::calculate() { return _left->calculate() * _right->calculate(); }
string Mul::getType() { return "mul"; }

/**Div**/
Div::Div(Expression* left, Expression* right) : BinaryOperator(left, right) {}
Div::~Div() = default;
double Div::calculate() {
  if (_right->calculate() == 0) {
    throw "division by zero";
  }
  return _left->calculate() / _right->calculate();
}
string Div::getType() { return "div"; }

/**UPlus**/
UPlus::UPlus(Expression* expression) : UnaryOperator(expression) {}
UPlus::~UPlus() = default;
double UPlus::calculate() { return _expression->calculate(); }
string UPlus::getType() { return "uplus"; }

/**UMinus**/
UMinus::UMinus(Expression* expression) : UnaryOperator(expression) {}
UMinus::~UMinus() = default;
double UMinus::calculate() { return _expression->calculate() * -1; }
string UMinus::getType() { return "uminus"; }

/**Value**/
Value::Value(double value) : _value(value) {}

double Value::calculate() { return _value; }
string Value::getType() { return "value"; }

/**Variable**/
Variable::Variable(string name, double value) {
  this->_name = name;
  this->_value = value;
}
double Variable::calculate() { return _value; }
string Variable::getType() { return "variable"; }
Variable& Variable::operator++() {
  _value++;
  return *this;
}
Variable& Variable::operator--() {
  _value--;
  return *this;
}
Variable& Variable::operator+=(double num) {
  _value = _value + num;
  return *this;
}
Variable& Variable::operator-=(double num) {
  _value = _value - num;
  return *this;
}
Variable& Variable::operator++(int) {
  _value++;
  return *this;
}
Variable& Variable::operator--(int) {
  _value--;
  return *this;
}
void Variable::setValue(double value) { this->_value = value; }
string Variable::getName() { return this->_name; }
double Variable::getValue() { return this->_value; }

/**Interpreter**/
Interpreter::Interpreter() = default;
Interpreter::~Interpreter() {
  for (Variable* v:this->_variables) {
    if (v != nullptr) {
      delete v;
    }
  }
}
void Interpreter::setVariables(string input) {

  if (!validateVariableExpression(input, '=') || !validateVariableExpression(input, ';')) {
    throw "illegal variable assignment!";
  }

  string delimiter = ";", token, name, value;
  size_t pos = 0;
  while ((pos = input.find(delimiter)) != string::npos) {
    token = input.substr(0, pos);
    input.erase(0, pos + delimiter.length());
    name = token.substr(0, token.find('='));
    value = token.substr(token.find('=') + 1);

    if (!validateVariableName(name) || !validateVariableValue(value)) {
      throw "illegal variable assignment!";
    }

    Variable* variable = new Variable(name, (stod(value)));
    addToArr(variable);
  }
  token = input.substr(0, pos);
  input.erase(0, pos + delimiter.length());
  name = token.substr(0, token.find('='));
  value = token.substr(token.find('=') + 1);

  if (!validateVariableName(name) || !validateVariableValue(value)) {
    throw "illegal variable assignment!";
  }

  Variable* variable = new Variable(name, (stod(value)));
  addToArr(variable);
}
Expression* Interpreter::interpret(string input) {
  queue<Expression*> output;
  output = infixToPostfix(input);
  Expression* finalExpression = integrateExpressions(output);
  return finalExpression;
}
bool Interpreter::isOperand(const char& c) { return c >= '0' && c <= '9'; }
bool Interpreter::isOperator(const char& c) { return c == '+' || c == '-' || c == '*' || c == '/'; }
bool Interpreter::hasHigherPrec(const char& top, const char& c) {
  if (c == '+' || c == '-') {
    if (top == '*' || top == '/')
      return true;
  }
  return false;
}
bool Interpreter::isOpeningParentheses(const char c) { return c == '('; }
bool Interpreter::isClosingParentheses(const char c) { return c == ')'; }
void Interpreter::addToArr(Variable* variable) {
  int pos = 0;
  for (Variable* ptr : this->_variables) {
    if (ptr == nullptr) { break; }
    if (ptr->getName() == variable->getName()) {
      ptr->setValue(variable->getValue());
      delete variable;
      return;
    }
    pos++;
  }
  _variables[pos] = variable;
}
void Interpreter::replaceAll(string& str, const string& from, const string& to) {
  if (from.empty())
    return;
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}
Value* Interpreter::getWholeValue(string input, int pos, int* posAfter) {

  if (pos == (signed) input.length() - 1) {
    Value* v = new Value(input[pos] - 48);
    *posAfter = pos;
    return v;
  }

  int originalPos = pos;
  while (pos < input.length() && (isOperand(input.at(pos)) || input.at(pos) == '.')) {
    pos++;
  }
  string str = input.substr(originalPos, pos);
  Value* v = new Value(stod(str));
  *posAfter = pos;
  return v;
}
Expression* Interpreter::createExpressionFromStack(stack<char>* stack) {
  Expression* e = nullptr;

  //temporary pop top element
  char top = stack->top();
  stack->pop();
  char prevTop = ' ';
  if (!stack->empty()) {
    prevTop = stack->top();
  }

  switch (top) {
    case '*':e = new Mul(nullptr, nullptr);
      break;
    case '/':e = new Div(nullptr, nullptr);
      break;
    case '+':
      if (prevTop == '$') {
        e = new UPlus(nullptr);
      } else {
        e = new Plus(nullptr, nullptr);
      }
      break;
    case '-':
      if (prevTop == '$') {
        e = new UMinus(nullptr);
      } else {
        e = new Minus(nullptr, nullptr);
      }
      break;
    default:break;
  }

  //return top element
  stack->push(top);
  return e;
}
queue<Expression*> Interpreter::infixToPostfix(string input) {
  stack<char> operators;
  queue<Expression*> output;
  int pos = 0, posAfter = 0;

  //replace variables with values
  for (Variable* ptr : this->_variables) {
    if (ptr == nullptr) { break; }
    string value = '(' + to_string(ptr->getValue()) + ')';
    replaceAll(input, ptr->getName(), value);
    replaceAll(input, " ", "");
  }

  if (!validateMathExpression(input)) {
    throw "illegal math expression";
  }

  //for every char in input string
  for (char c : input) {

    if (pos < posAfter) {
      pos++;
      continue;
    }

    if (isOperand(c)) {
      Value* v = getWholeValue(input, pos, &posAfter);
      output.push(v);
    } else if (isOperator(c)) {
      while (!operators.empty()
          && !isOpeningParentheses(operators.top())
          && hasHigherPrec(operators.top(), c)) {
        //push top of operators stack into output queue
        Expression* e = createExpressionFromStack(&operators);
        if (e != nullptr) {
          output.push(e);
        }
        operators.pop();
      }
      if (c == '+' || c == '-') {
        if (pos == 0 || input[pos - 1] == '(') {
          operators.push('$');
        }
      }
      operators.push(c);
    } else if (isOpeningParentheses(c)) {
      // c = '('
      operators.push(c);
    } else if (isClosingParentheses(c)) {
      // c = ')'
      while (!operators.empty()
          && !isOpeningParentheses(operators.top())) {
        Expression* e = createExpressionFromStack(&operators);
        if (e != nullptr) {
          output.push(e);
        }
        operators.pop();
      }
      operators.pop();
    }
    pos++;
  }// end of for loop. end of input

  //empty operators stack and push to output
  while (!operators.empty()) {
    Expression* e = createExpressionFromStack(&operators);
    if (e != nullptr) {
      output.push(e);
    }
    operators.pop();
  }

  return output;
}
Expression* Interpreter::integrateExpressions(queue<Expression*> output) {
  stack<Expression*> expressions;
  while (!output.empty()) {
    Expression* e = output.front();
    Expression* eLeft;
    Expression* eRight;

    if (typeid(*e) == typeid(Value)) {
      expressions.push(output.front());
    } else if (typeid(*e) == typeid(Mul)) {
      eRight = expressions.top();
      expressions.pop();
      eLeft = expressions.top();
      expressions.pop();
      Mul* mul = new Mul(eLeft, eRight);
      expressions.push(mul);
      delete e;
    } else if (typeid(*e) == typeid(Div)) {
      eRight = expressions.top();
      expressions.pop();
      eLeft = expressions.top();
      expressions.pop();
      Div* div = new Div(eLeft, eRight);
      expressions.push(div);
      delete e;
    } else if (typeid(*e) == typeid(Plus)) {
      eRight = expressions.top();
      expressions.pop();
      eLeft = expressions.top();
      expressions.pop();
      Plus* plus = new Plus(eLeft, eRight);
      expressions.push(plus);
      delete e;
    } else if (typeid(*e) == typeid(Minus)) {
      eRight = expressions.top();
      expressions.pop();
      eLeft = expressions.top();
      expressions.pop();
      Minus* minus = new Minus(eLeft, eRight);
      expressions.push(minus);
      delete e;
    } else if (typeid(*e) == typeid(UPlus)) {
      eRight = expressions.top();
      expressions.pop();
      UPlus* uPlus = new UPlus(eRight);
      expressions.push(uPlus);
      delete e;
    } else if (typeid(*e) == typeid(UMinus)) {
      eRight = expressions.top();
      expressions.pop();
      UMinus* uMinus = new UMinus(eRight);
      expressions.push(uMinus);
      delete e;
    }
    output.pop();
  }
  return expressions.top();
}
bool Interpreter::validateVariableExpression(const string expression, const char symbol) {
  int pos = 0;
  //check that the symbol does not appear twice in a row
  for (char c: expression) {
    if (c == symbol) {
      if (pos == 0) {
        continue;
      } else {
        if (expression[pos - 1] == symbol) {
          return false;
        }
      }
    }
    pos++;
  }

  return true;
}
bool Interpreter::validateVariableName(const string name) {

  //check if first char is a digit
  if (name[0] >= '0' && name[0] <= '9') {
    return false;
  }

  //check every char is 0-9, A-z, or '_'
  for (char c: name) {
    if (!(c >= '0' && c <= '9') && !(c >= 'A' && c <= 'z') && c != '_') {
      return false;
    }
  }

  return true;
}
bool Interpreter::validateVariableValue(const string value) {
  int pos = 0;
  bool foundPeriod = false;
  for (char c: value) {
    //first char can be '-'
    if (pos == 0) {
      if (c == '-') {
        continue;
      }
    }
    //check that every digit is 0-9 or '.'
    if (!(c >= '0' && c <= '9') && c != '.') {
      return false;
    }
    // check there is no '.' twice
    if (c == '.') {
      if (!foundPeriod) {
        foundPeriod = true;
      } else {
        return false;
      }
    }
    pos++;
  }
  return true;
}
bool Interpreter::validateMathExpression(const string expression) {
  int pos = 0;
  for (char c:expression) {

    if (!(c >= '0' && c <= '9') && c != '(' && c != ')' && c != '+' && c != '-' && c != '*' && c != '/' && c != '.'
        && c != ' ') {
      return false;
    }
    if (pos == 0) {
      pos++;
      continue;
    }
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '.') {
      if (expression[pos - 1] == '+' || expression[pos - 1] == '-' || expression[pos - 1] == '*'
          || expression[pos - 1] == '/' || expression[pos - 1] == '.') {
        return false;
      }
    }
    pos++;
  }

  return true;
}
