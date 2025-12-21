#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "bounds.h"
#include "image.h"
#include "func.h"
#include "fill.h"
#include "expr_parser.h"

using std::vector;

class Plot {
private:
  // TODO: add fields to represent plot bounds, functions, fills, etc.
  Bounds bounds;
  vector<Function*> funcs; 
  std::map<std::string, Color> func_colors;
  vector<Fill> fills;
  
  // value semantics are prohibited
  Plot(const Plot &);
  Plot &operator=(const Plot &);

public:
  Plot();

  // Deconstructor
  ~Plot();

  // getters
  int get_width() { return bounds.getWidth(); }
  int get_height() { return bounds.getHeight(); }
  float getXMin() { return bounds.getXMin(); }
  float getXMax() { return bounds.getXMax(); }
  float getYMin() { return bounds.getYMin(); }
  float getYMax() { return bounds.getYMax(); }
  const vector<Function*>& getFunctions() const { return funcs; }
  std::map<std::string, Color> getFuncColors() { return func_colors; }
  vector<Fill> getFills() {return fills;}

  // setters
  void setBounds(std::istringstream &ss);
  void setColor(std::istringstream &ss);
  void setFunc(std::istringstream &ss);
  void setFill(std::istringstream &ss, int type);
  
};

#endif // PLOT_H
