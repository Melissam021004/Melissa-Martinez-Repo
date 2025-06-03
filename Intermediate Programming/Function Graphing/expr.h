#ifndef EXPR_H
#define EXPR_H

#include <vector>
#include <string>
#include <iostream>

// Base expression class
class Expr {
private:

  // value semantics are prohibited
  Expr(const Expr &);
  Expr &operator=(const Expr &);

protected:
 std::vector<Expr*> children;

public:
  Expr();
  virtual ~Expr();
  virtual std::string type() = 0;    
  virtual double eval(double x) const = 0;

// adds children
void add_child(Expr* arg) { children.push_back(arg); }


};


class VariableX : public Expr {
public:
    VariableX () {}
    virtual ~VariableX() {}
    virtual std::string type() { return "x"; }; 
    virtual double eval(double x) const ;
};

class PiValue : public Expr {
public:
    PiValue () {}
    virtual ~PiValue() {}
    virtual std::string type() { return "pi"; }; 
    virtual double eval(double x) const ;
};

class LiteralValue : public Expr {
private:
    double value;
public:
    LiteralValue(double val);
    virtual ~LiteralValue() {}
    virtual std::string type() { return "literal"; }; 
    virtual double eval(double x) const ;
};

class SinFunction : public Expr {
public:
    SinFunction () {}
    virtual ~SinFunction() {}
    virtual std::string type() { return "sin"; }; 
    virtual double eval(double x) const ;
};

class CosFunction : public Expr {
public:
    CosFunction () {}
    virtual ~CosFunction() {}
    virtual std::string type() { return "cos"; }; 
    virtual double eval(double x) const ;
};

class PlusFunction : public Expr {
public:
    PlusFunction () {}
    virtual ~PlusFunction() {}
    virtual std::string type() { return "+"; }; 
    virtual double eval(double x) const ;
};

class MinusFunction : public Expr {
public:
    MinusFunction () {}
    virtual ~MinusFunction() {}
    virtual std::string type() { return "-"; }; 
    virtual double eval(double x) const ;
};

class MultiplyFunction : public Expr {
public:
    MultiplyFunction () {}
    virtual ~MultiplyFunction() {}
    virtual std::string type() { return "*"; }; 
    virtual double eval(double x) const ;
};

class DivideFunction : public Expr {
public:
    DivideFunction () {}
    virtual ~DivideFunction() {}
    virtual std::string type() { return "/"; }; 
    virtual double eval(double x) const ;
};

#endif // EXPR_H
