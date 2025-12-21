#ifndef BOUNDS_H
#define BOUNDS_H

class Bounds {
private:
  float xmin;
  float ymin;
  float xmax;
  float ymax;
  int ydim;
  int xdim;

public:
  // Default Contructor
  Bounds() : xmin(0), ymin(0), xmax(0.0), ymax(0.0), ydim(0), xdim(0) {}
  
  // Special Constructor
  Bounds(float minx, float miny, float maxx, float maxy, int dimy, int dimx) :
    xmin(minx), ymin(miny), xmax(maxx), ymax(maxy), ydim(dimy), xdim(dimx) {}

    // Getters
  int getWidth() { return xdim; }
  int getHeight() { return ydim; }
  float getXMin() { return xmin; }
  float getXMax() { return xmax; }
  float getYMin() { return ymin; }
  float getYMax() { return ymax; }

  // Setters
  void setWidth(int w) {xdim = w;}
  void setHeight(int h) {ydim = h;}
  void setXMin(float m) {xmin = m;}
  void setXMax(float m) {xmax = m;}
  void setYMin(float m) {ymin = m;}
  void setYMax(float m) {ymax = m;}

};

#endif // BOUNDS_H
