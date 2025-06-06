#include "func.h"

Function::Function(const std::string &name, Expr *expr)
  : m_name(name)
  , m_expr(expr) {
}

Function::~Function() {
  delete m_expr;
}
