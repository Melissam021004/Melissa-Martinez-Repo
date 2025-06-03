#include <cstddef>
#include <string>
#include <sstream>
#include <memory>
#include <deque>
#include "exception.h"
#include "expr.h"
#include "expr_parser.h"

ExprParser::ExprParser() {
}

ExprParser::~ExprParser() {
}


Expr* ExprParser::parse(std::istream &in) {

  std::vector<std::string> tokens;
  std::string token;

  // Puts entire string into a vector
  while (in >> token) {
    tokens.push_back(token);
  }

  if (tokens.size() > 1 && (tokens.front() == "x" || tokens.front() == "pi" || isLiteralNumber(tokens.front()))) {
    throw PlotException("Invalid function");
  }

  // parses string
  expression = parseExpr(tokens);

  return expression;

}

Expr* ExprParser::parseExpr(std::vector<std::string>& tokens) {

  Expr* parent = nullptr;

  // first string
  std::string n = tokens.front();

  // If x makes an X expr
  if (n == "x" ) {
      tokens.erase(tokens.begin());
               
      return new VariableX();
    }
  // If pi makes an pi expr
  else if ( n == "pi") {
    tokens.erase(tokens.begin());  
    return new PiValue();
  }
  // If literal number makes an literal number expr
  else if (isLiteralNumber(n)) {
    tokens.erase(tokens.begin());  
    return new LiteralValue(std::stod(n));
    
  }
  // if a (
  else if (n == "(") { 

    //erase and get next string
    tokens.erase(tokens.begin()); 
    n = tokens.front(); 
    tokens.erase(tokens.begin()); 

    //checks to see if rest of functions
    parent = isSupportedFunction(n);

    if (parent == nullptr) {
      // throw exception - Invalid function name
      throw PlotException("Invalid function name");
    }

    // continues through rest of vector adding as children
    while (tokens.front() != ")") {
      Expr* arg = parseExpr(tokens);
      parent->add_child(arg);
    }

    // Remove ')'
    tokens.erase(tokens.begin()); 

  } else {
            // throw exception - Unexpected token
        throw PlotException("Error parsing expression");
  }

  return parent;

}


int ExprParser::isLiteralNumber(std::string n) {
  int number = 1;
  int period = 0;
  char comp;

  // goes through entire string
  for (size_t i = 0; i < n.size(); i++) {

    //gets char
    comp = n.at(i);

    // if valid number 
    if (comp >= '0' && comp <= '9') {
      continue;
    }
    else if (comp == '.' && period == 0) {
      period = 1;
      continue;
    }
    //not valid 
    else {
      number = 0;
    }
  }

  //just a period 
  if (period == 1 && n.size() == 1) {
    number = 0;
  }

  return number;
}

Expr* ExprParser::isSupportedFunction(std::string n) {

  // checks to see if one of the supported functions and returns it
  if (n == "sin") { 
    return new SinFunction();
  }
  else if (n == "cos") {
    return new CosFunction() ;
  }
  else if (n == "+") {
    return new PlusFunction() ;
  }
  else if (n == "-") {
    return new MinusFunction() ;
  }
  else if (n == "*") {
    return new MultiplyFunction() ;
  }
  else if (n == "/") {
    return new DivideFunction() ;
  }
  // else it returns null 
  else {
  return nullptr;
  }
}
