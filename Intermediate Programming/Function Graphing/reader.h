#ifndef READER_H
#define READER_H
#include <iostream>
#include <map>
#include <sstream>
#include <cstdint>
#include "exception.h"
#include "plot.h"
#include "expr_parser.h"
#include "fill.h"

class Reader {
private:
  // value semantics are prohibited
  Reader(const Reader &);
  Reader &operator=(const Reader &);

public:
  Reader();
  ~Reader();

  void func_directive(std::istringstream &in);

  // read plot description from given istream;
  // throw a PlotException if any errors are found
  void read_input(std::istream &in, Plot &plot);
};

#endif // READER_H
