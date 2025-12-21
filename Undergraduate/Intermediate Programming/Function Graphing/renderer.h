#ifndef RENDERER_H
#define RENDERER_H

#include "plot.h"
#include "image.h"
#include "func.h"

class Renderer {
private:
  // it's convenient to have these as fields, to avoid the need
  // to pass them explicitly to helper functions
  Plot &m_plot;
  Image *m_img;
  std::map<std::string, std::map<float,float>> vectorOfPixelMaps;
  // Map of X and Y for each function

  // value semantics prohibited
  Renderer(const Renderer &);
  Renderer &operator=(const Renderer &);

public:
  Renderer(Plot &plot);
  ~Renderer();

  Image *render();

  // handles the fill commands
  void handleFills(std::map<std::string, std::map<float,float>> maps);

  // calculates the functions
  void calcFunctions(Plot &plot);

  // draws the functions
  void drawFunctions(std::map<std::string, std::map<float,float>> maps);

  //Returns the map of strings and their corresponging pixel data points
  std::map<std::string, std::map<float,float>>  getVector() { return vectorOfPixelMaps; }

private:
};

#endif // RENDERER_H
