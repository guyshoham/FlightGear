//
// Created by Tsand on 11/7/2019.
//

#ifndef UNTITLED_EX1_H
#include <iostream>
#include <stack>
#include "Expression.h"
#define UNTITLED_EX1_H

class Value : public Expression {
    const double value;
public:
    explicit Value(double value);
    virtual ~Value();
    double calculate();
};

class Variable : public Expression {
    string name;
    double value;
public:
    Variable(string name1, double value1);
    virtual ~Variable();
    double calculate();
    string getName();
    double getValue();

    Variable& operator++();

    Variable& operator--();

    Variable& operator+=(double e);

    Variable& operator-=(double e);

    Variable& operator++(int e);

    Variable& operator--(int e);


};

class UnaryOperator : public Expression {
    Expression* expression;
protected:
    UnaryOperator(Expression* expression1);

public:
    double calculate();
    virtual ~UnaryOperator();
};

class UPlus : public UnaryOperator {
    Expression* expression;
public:
    UPlus(Expression* expression1);
    double calculate();
    virtual ~UPlus();
};
class UMinus : public UnaryOperator {
    Expression* expression;
public:
    UMinus(Expression* expression1);
    double calculate();
    virtual ~UMinus();
};

class BinaryOperator : public Expression {
protected:
    Expression* right;
    Expression* left;
public:
    BinaryOperator(Expression* rValue, Expression* lValue);
    virtual ~BinaryOperator();

    double calculate();
};

class Plus : public BinaryOperator {
    Expression* right;
    Expression* left;
public:
    Plus(Expression* rValue, Expression* lValue);
    double calculate();
    virtual ~Plus();

};
class Minus : public BinaryOperator {
    Expression* right;
    Expression* left;
public:
    Minus(Expression* rValue, Expression* lValue);
    double calculate();
    virtual ~Minus();

};
class Mul : public BinaryOperator {
    Expression* right;
    Expression* left;
public:
    Mul(Expression* rValue, Expression* lValue);
    double calculate();
    virtual ~Mul();

};
class Div : public BinaryOperator {
    Expression* right;
    Expression* left;
public:
    Div(Expression* rValue, Expression* lValue);
    double calculate();
    virtual ~Div();

};

class Interpreter {
    Variable* variables[10];
    int size;
public:
    Interpreter();
    Expression* interpret(string expression);

    void setVariables(string expression);

    string switchVariables(string expression);
    int findLastDigit(int i, string expression);

// Function to verify whether an operator has higher precedence over other
    int HasHigherPrecedence(char operator1, char operator2);

// Function to verify whether a character is operator symbol or not.
    bool IsOperator(char C);

// Function to verify whether a character is alphanumeric character (letter or numeric digit) or not.
    bool IsOperand(char C);

    int GetOperatorWeight(char op);
    virtual ~Interpreter();
};

#endif //UNTITLED_EX1_H
