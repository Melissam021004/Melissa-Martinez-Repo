#ifndef FILL_H
#define FILL_H

#include <string>
#include <vector>
#include "image.h"

class Fill {
private:
  
  //0 for above, 1 for below, 2 for in between
  int type;
  float opacity;
  Color c;
  std::vector<std::string> funcs;

public:
  Fill();
  ~Fill();

  // setters
  void setType(int a) {type = a;}
  void setOpacity(float a) {opacity = a;}
  void setColor(Color a) { c = a;}
  void addFuncName(std::string a) {funcs.push_back(a);}

  // getters
  int getType() {return type;}
  float getOpacity() {return opacity;}
  Color getColor() { return c;}
  std::string getName() {return funcs[0];}
  std::string getFirstName() {return funcs[0];}
  std::string getSecondName() {return funcs[1];}
};

#endif // FILL_H
