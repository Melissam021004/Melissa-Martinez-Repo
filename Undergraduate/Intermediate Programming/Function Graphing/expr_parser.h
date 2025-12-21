#ifndef FN_PARSER_H
#define FN_PARSER_H

#include <iostream>
#include "expr.h"

class ExprParser {
private:
  Expr* expression;
  // value semantics are prohibited
  ExprParser(const ExprParser &);
  ExprParser &operator=(const ExprParser &);

public:
  ExprParser();
  ~ExprParser();

  Expr* parse(std::istream &in); // Parses an expression from an input stream
  Expr* parseExpr(std::vector<std::string>& tokens); // Parses an expression from a vector of tokens
  int isLiteralNumber(std::string n); // Checks if a string is a literal number
  Expr* isSupportedFunction(std::string n); // Checks if a string is a supported function

  

};

#endif // FN_PARSER_H
