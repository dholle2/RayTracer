#include "PlaneChecker.h"
#include <iostream>
#include "Maths.h"
#include <math.h>
using namespace std;

  PlaneChecker::PlaneChecker(void)
  {
    outline_width = 0;
    size = 5;
    color1 = RGBColor(1,1,1);
    color2 = RGBColor(0,0,0);
    outline_color = RGBColor(0,1,0);
  }

  PlaneChecker::~PlaneChecker(void)
  {}

/*
  PlaneChecker*
  PlaneChecker::clone(void) const {
  	return (new PlaneChecker(*this));
  }
*/


void
PlaneChecker::set_color(RGBColor& c1, RGBColor& c2, RGBColor& c3){
  color1 = c1;
  color2 = c2;
  outline_color = c3;
}

void
PlaneChecker::set_size(float s){
  size = s;
}

void
PlaneChecker::set_outline_width(float w){
  outline_width = w;
}

RGBColor&
PlaneChecker::get_color(const ShadeRec& sr){

  float x = sr.local_hit_point.x;
  float z = sr.local_hit_point.z;
  int ix = floor(x / size);
  int iz = floor(z / size);
  float fx = x / size - ix;
  float fz = z / size - iz;
  float width = 0.5 * outline_width / size;
  bool in_outline = (fx < width || fx > 1.0 - width) || (fz < width || fz > 1.0 - width);

  if( (ix + iz) % 2 == 0){
    if(!in_outline){
      return color1;
    }
  }else{
    if(!in_outline){
      return color2;
    }
  }

  return outline_color;
}
