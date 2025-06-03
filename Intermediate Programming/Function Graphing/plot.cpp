#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include "func.h"
#include "plot.h"
#include "exception.h"
#include "expr.h"
#include <sstream>
#include <stdexcept>

Plot::Plot() {
}

Plot::~Plot() {
  for (size_t i = 0; i < funcs.size(); ++i) {
    delete funcs[i];
    funcs[i] = nullptr; // Set the pointer to nullptr after deleting
  }
}

// Assuming Plot and Bounds classes are defined elsewhere

void Plot::setBounds(std::istringstream &ss) {
    float temp;
    
    if (!(ss >> temp)) {
        throw PlotException("Missing xmin");
    }
    bounds.setXMin(temp);

    if (!(ss >> temp)) {
        throw PlotException("Missing ymin");
    }
    bounds.setYMin(temp);

    if (!(ss >> temp)) {
        throw PlotException("Missing xmax");
    }
    float xmax = temp; 
    bounds.setXMax(temp);

    if (!(ss >> temp)) {
        throw PlotException("Missing ymax");
    }
    float ymax = temp; 
    bounds.setYMax(temp);

    if (xmax < bounds.getXMin()) {
        throw PlotException("Xmin is not less than xmax");
    }

    if (ymax < bounds.getYMin()) {
        throw PlotException("Ymin is not less than ymax");
    }

    if (!(ss >> temp)) {
        throw PlotException("Missing width");
    }
    bounds.setWidth(temp);

    if (!(ss >> temp)) {
        throw std::invalid_argument("Missing height");
    }
    bounds.setHeight(temp);

    // Check if image dimensions are valid
    if (bounds.getWidth() <= 0) {
        throw PlotException("Width should be positive");
    }

    if (bounds.getHeight() <= 0) {
        throw PlotException("Height should be positive");
    }
}

void Plot::setColor(std::istringstream &ss){
    std::string name;
    ss >> name;

    //Checking if the name matches a current function
    bool isFunc = false;

    for(size_t i = 0; i < funcs.size(); i++){
        if(name == funcs[i]->get_name()){
            isFunc = true;
            break;
        }
    }

    if(!isFunc){
        throw PlotException("Attempted to set color for an invalid function");
        return;
    }

    if(func_colors.find(name) != func_colors.end()){
        //Trying to set a function color twice
        throw PlotException("Attempt to set a function to multiple colors");
        return;
    }

    int val;
    Color c;

    //Red color
    if(ss >> val){
        if(val < 0 || val > 255){
            throw PlotException("Invalid color value");
            return;
        }
        c.r = val;
    }
    else{
        throw PlotException("Insufficient color arguments");
        return;
    }

    //G color
    if(ss >> val){
        if(val < 0 || val > 255){
            throw PlotException("Invalid color value");
            return;
        }
        c.g = val;
    }
    else{
        throw PlotException("Insufficient color arguments");
        return;
    }

    //Blue color
    if(ss >> val){
        if(val < 0 || val > 255){
            throw PlotException("Invalid color value");
            return;
        }
        c.b = val;
    }
    else{
        throw PlotException("Insufficient color arguments");
        return;
    }

    func_colors[name] = c;

}

void Plot::setFunc(std::istringstream &ss){

  std::string name;
  ss >> name;
  ExprParser a;

  // parses through the input string
  Expr* temp = a.parse(ss);

  // adds to a function
  Function* newFunction = new Function(name, temp);

  // adds to vector
  funcs.push_back(newFunction);

}

void Plot::setFill(std::istringstream &ss, int type){

    std::string name;
    std::string funcname;
    float op;
    int temp;
    bool boo = false;
    Fill fill;
    fill.setType(type);

    //Fill above or fill below
    if(type == 0 || type == 1){

        //Handling function name
        if(ss >> name){
            boo = false;
            //Checking for valid function name
            for(size_t i = 0; i < funcs.size(); i++){
                funcname = funcs[i]->get_name();
                if(funcname == name){
                    boo = true;
                }
            }
            if(boo){
                //Valid function name
                fill.addFuncName(name);
            }
            else{
                throw PlotException("Not a valid function name");
            }
        }
        else{
            //TODO: throw error
            throw PlotException("Did not pass any function names or fill specifications");
            
        }
    }
    //Fill between
    else if(type == 2){

        //First function name
        if(ss >> name){
            boo = false;
            //Checking for valid function name
            for(size_t i = 0; i < funcs.size(); i++){
                funcname = funcs[i]->get_name();
                if(funcname == name){
                    boo = true;
                    break;
                }
            }
            if(boo){
                //Valid function name
                fill.addFuncName(name);
            }
            else{

                throw PlotException("Invalid function name");
            }
        }
        else{

            throw PlotException("Did not pass any function names or fill specifications");
        }

        if(ss >> name){
            boo = false;
            //Checking for valid function name
            for(size_t i = 0; i < funcs.size(); i++){
                funcname = funcs[i]->get_name();
                if(funcname == name){
                    boo = true;
                    break;
                }
            }
            if(boo){
                //Valid function name
                fill.addFuncName(name);
            }
        }
        else{

            throw PlotException("Did not pass any function names or fill specifications");
        }

    }
    else{
        throw PlotException("Incorrect type");
    }

    //Getting opacity
    if(ss >> op){
        if(op < 0 || op > 1){
            throw PlotException("Invalid opacity");
        }
        else{
            fill.setOpacity(op);
        }
    }
    else{

        throw PlotException("Did not provide opacity as next argument");
    }

    //Getting RGB
    Color c;
    //Red
    if(ss >> temp){
        if(temp < 0 || temp > 255){

            throw PlotException("Invalid Color");
        }
    }
    else{

        throw PlotException("Did not specify color");
    }

    c.r = temp;

    //Green
    if(ss >> temp){
        if(temp < 0 || temp > 255){

            throw PlotException("Invalid Color");
        }
    }
    else{

        throw PlotException("Did not specify color");
    }
    c.g = temp;

    //Blue
    if(ss >> temp){
        if(temp < 0 || temp > 255){

            throw PlotException("Invalid Color");
        }
    }
    else{
        
        throw PlotException("Did not specify color");
    }
    c.b = temp;

    fill.setColor(c);
    fills.push_back(fill);
}