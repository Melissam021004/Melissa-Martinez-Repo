#include <iostream>
#include <map>
#include <sstream>
#include <cstdint>
#include "exception.h"
#include "plot.h"
#include "reader.h"
#include "expr_parser.h"
#include "fill.h"

#include <cassert>
#include <cstddef>
#include <string>
#include "func.h"
#include "expr.h"

using std::string;
//using std::find;
Reader::Reader() {
}

Reader::~Reader() {
}

void func_directive(std::istringstream &in){
  string name;
  in >> name;

}
// Loops over and over until reach end of input file.
// Read input line, break up into vector of words to iterate through, then fill in plot with data
void Reader::read_input(std::istream &in, Plot &plot) {

  string str;
  std::map<string, int> Directives;
  Directives["Plot"] = 0;
  Directives["Function"] = 1;
  Directives["Color"] = 2;
  Directives["FillBetween"] = 3;
  Directives["FillAbove"] = 4;
  Directives["FillBelow"] = 5;

  while(std::getline(in, str)){

    //Checking if the line was obtained
    if(str.empty()){
      break;
    }

    //Putting the line in a string stream
    std::istringstream ss(str);

    //Getting the first word (directive) of the line
    string directive;
    ss >> directive;
    int d = Directives[directive];

    switch(d){

      //Plot Bounds
      case 0:
        plot.setBounds(ss);
        break;

      //Function
      case 1: {
        plot.setFunc(ss);
        break;
      }
      
      //Color
      case 2:
        plot.setColor(ss);
        break;
      
      //Fill Between
      case 3:
        plot.setFill(ss, 2);
        break;

      //Fill Above
      case 4:
        plot.setFill(ss, 0);
        break;

      //Fill Below
      case 5:
        plot.setFill(ss, 1);
        break;
      
      //Invalid Directive
      default:
        throw PlotException("Command not valid");
        break;
    }

  }

}
