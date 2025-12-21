#include <cmath>
#include "exception.h"
#include "expr.h"
#include <cstddef>
#include <iostream>

// Expr (base class)
Expr::Expr() {
}

Expr::~Expr() {
  if (children.size() != 0) {
    // if children go through and delete them
    for (size_t i = 0; i < children.size(); ++i) {
        delete children[i];
    }
  }
}


double VariableX::eval(double x) const {
    return x;
}


double PiValue::eval(double x) const {
  x = M_PI;
    return x;
}

LiteralValue::LiteralValue(double val) : value(val) {}

double LiteralValue::eval(double x) const {
  x = value;
    return x;
}


double SinFunction::eval(double x) const {
  // not one argument 
  if (children.size() != 1) {
    throw PlotException("There is not exactly one argument for sin function.");
  }
    double answer = std::sin(children[0]->eval(x));
    return answer;
}


double CosFunction::eval(double x) const {
    // not one argument 
  if (children.size() != 1) {
    throw PlotException("There is not exactly one argument for cos function.");
  }
    double answer = std::cos(children[0]->eval(x));
    return answer;
}


double PlusFunction::eval(double x) const {
    double sum = 0;
    for (size_t i = 0; i < children.size(); i++) {
        sum += children[i]->eval(x);
    }
    return sum;
}


double MinusFunction::eval(double x) const {
  // not two arguments
  if (children.size() != 2) {
    throw PlotException("There are not two arguments for subtraction.");
  }
    double difference = children[0]->eval(x) - children[1]->eval(x);
    
    return difference;
}


double MultiplyFunction::eval(double x) const {
    double product = 1;
    for (size_t i = 0; i < children.size(); i++) {
        product *= children[i]->eval(x);
    }
    return product;
}


double DivideFunction::eval(double x) const {
    // not two arguments
  if (children.size() != 2) {
    throw PlotException("There are not two arguments for division.");
  }
    double denominator = children[1]->eval(x);
    // if denom is 0
    if (denominator == 0) {
       throw PlotException("Division by zero");
    }
    double division = children[0]->eval(x) / denominator;
    return division;
}
