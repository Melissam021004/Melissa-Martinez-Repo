#include <algorithm>
#include <cstddef>
#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include "exception.h"
#include "renderer.h"
#include "func.h"
#include "expr.h"
#include "plot.h"
#include "image.h"

//#define DEBUG_FILL
//#define DEBUG_PLOT

Renderer::Renderer(Plot &plot)
  : m_plot(plot)
  , m_img(nullptr) {

}

Renderer::~Renderer() {
  // Note: the Renderer object does not "own" the Image object,
  // since the render() member function transfers ownership of
  // the Image object to the caller (in the main function)
}

Image *Renderer::render() {
  int width = m_plot.get_width();
  int height = m_plot.get_height();

  // the unique_ptr will take care of deleting the Image object
  // if an exception is thrown
  std::unique_ptr<Image> img(new Image(width, height));
  m_img = img.get();  

  calcFunctions(m_plot);
  handleFills(vectorOfPixelMaps);
  drawFunctions(vectorOfPixelMaps);

  return img.release();
}

void Renderer::calcFunctions(Plot &plot) {

  //Getting the functions and colors
  std::map<std::string, Color> funcColors = plot.getFuncColors();
  const vector<Function*>& funcs = plot.getFunctions();

  //Going through each function, evaluating, and storing
  for (size_t v = 0; v < funcs.size(); v++) {

    //Map to store data in column, row order
    std::map<float, float> map;

    //Going through every x value/pixel
    for (double x = 0; x < plot.get_width(); x++) {
      //Calculating x value for every pixel 
      double gridX = (double) plot.getXMin() + ((double) x / (double) plot.get_width()) * ((double) plot.getXMax() - (double) plot.getXMin());
      
      //Evaluating the y value for the above x
      double yBasedOnGridX = (double) funcs[v]->get_expr()->eval((double) gridX);

      //Converting the previous y value into its pixel equivalent
      double gridY = (double) plot.get_height() - ((double) 1) - floor(((double) yBasedOnGridX - (double) plot.getYMin())/((double) plot.getYMax()- (double) plot.getYMin()) * (double) plot.get_height());
      
      //Storing the column pixel value with its row pixel value
      map[x] = (double) gridY;
    }

    //Storing data for each function
    vectorOfPixelMaps[funcs[v]->get_name()] = map;
  }
}

void Renderer::handleFills(std::map<std::string, std::map<float,float>> maps){
  //note to self: maps is the x and y value
  if(m_plot.getFills().size() == 0){
    //No fills
    return;
  }

  //Go through each fill
  for(size_t i = 0; i < m_plot.getFills().size(); i++){
    //Data for the current fill
    Fill curr = (m_plot.getFills())[i];
    float op = curr.getOpacity();
    int type = curr.getType();
    std::string funcName;
    std::map<float, float> currMap;

    //Fill above and below
    if(type == 0 || type == 1){
      funcName = curr.getName();
      currMap = maps[funcName];
      std::map<float,float>::iterator it = currMap.begin();

      //Going through each x
      int col = 0;
      int row;
      int index;
      //Going through each x in currMap
      while(it != currMap.end()){
        //Filling every pixel above that y value for the current x val;
        col = it->first;
        row = it->second;
        
        //Fill above
        if(type == 0){
          for(int i = row - 1; i >= 0; i--){
            index = i * m_plot.get_width() + col;
            Color old = m_img->get_color(index);

            //Making new color by blending with previous color
            Color c;
            c.r = floor((1-op) * old.r + (op * curr.getColor().r));
            c.g = floor((1-op) * old.g + (op * curr.getColor().g));
            c.b = floor((1-op) * old.b + (op * curr.getColor().b));

            //Setting pixel
            m_img->set_color(index, c);
          }
        }
        //Fill below
        else if(type == 1){
          for(int i = row + 1; i < m_plot.get_height(); i++){
            index = i * m_plot.get_width() + col;
            Color old = m_img->get_color(index);

            //Making new color by blending with previous color
            Color c;
            c.r = floor((1-op) * old.r + (op * curr.getColor().r));
            c.g = floor((1-op) * old.g + (op * curr.getColor().g));
            c.b = floor((1-op) * old.b + (op * curr.getColor().b));

            //Setting pixel
            m_img->set_color(index, c);
          }
        }
        it++;

      }
    }

    //Fill betweem
    else if(type == 2){
      std::string funcName1 = curr.getFirstName();
      std::string funcName2 = curr.getSecondName();
      std::map<float, float> funcMap1 = maps[funcName1];
      std::map<float, float> funcMap2 = maps[funcName2];

      //The column values should be the same for both function
      std::map<float,float>::iterator it = funcMap1.begin();

      int col;
      int row1;
      int row2;
      int index;

      //Iterating through each x pixel value
      while(it != funcMap1.end()){
        col = it->first;
        row1 = it->second;
        row2 = funcMap2[col];

        if(row1 > row2){
          for(int i = row2 + 1; i < row1; i++){
            index = i * m_plot.get_width() + col;
            Color old = m_img->get_color(index);

            //Making new color by blending with previous color
            Color c;
            c.r = floor((1-op) * old.r + (op * curr.getColor().r));
            c.g = floor((1-op) * old.g + (op * curr.getColor().g));
            c.b = floor((1-op) * old.b + (op * curr.getColor().b));

            //Setting pixel
            m_img->set_color(index, c);
          }
        }
        else if(row2 > row1){
          for(int i = row1 + 1; i < row2; i++){
            index = i * m_plot.get_width() + col;
            Color old = m_img->get_color(index);

            //Making new color by blending with previous color
            Color c;
            c.r = floor((1-op) * old.r + (op * curr.getColor().r));
            c.g = floor((1-op) * old.g + (op * curr.getColor().g));
            c.b = floor((1-op) * old.b + (op * curr.getColor().b));

            //Setting pixel
            m_img->set_color(index, c);
          }
        }
        it++;
      }
    }
    else{
      
      throw PlotException("Invalid fill method");
    }
  }
}

void Renderer::drawFunctions(std::map<std::string, std::map<float,float>> maps){

  std::map<std::string, Color> funcColors = m_plot.getFuncColors();
  //Iterator to go through each function
  std::map<std::string, std::map<float,float>>::iterator map = maps.begin();

  //Going through each function
  std::string name;
  while(map != maps.end()){
    name = map->first;
    std::map<float,float> points = map -> second;
    Color c;

    if(funcColors.find(name) == funcColors.end()){
      //No color defined
      c.r = 255;
      c.g = 255;
      c.b = 255;
    }
    else{
      c = funcColors[name];
    }

    //Going through each column
    int row;
    int col;
    int index;
    std::map<float,float>::iterator it = points.begin();
    while(it != points.end()){
      col = it->first;
      row = it->second;
      index = row * m_plot.get_width() + col;

      //Center point
      m_img->set_color(index, c);

      //Left point
      if(col != 0){
        m_img->set_color(index - 1, c);
      }

      //Right point
      if(col != m_plot.get_width() - 1){
        m_img->set_color(index + 1, c);
      }

      //Bottom point
      if(row != m_plot.get_height() - 1){
        m_img->set_color(index + m_plot.get_width(), c);
      }

      //Top point
      if(row != 0){
        m_img->set_color(index - m_plot.get_width(), c);
      }
      
      it++;
    }
    map++;
  }

}