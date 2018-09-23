#include "Directional.h"

Directional::Directional(void)
:Light(),
ls(1.0),
color(1.0),
dir(0,-1, 0)
{}

Directional::~Directional(void)
{}

void
Directional::set_direction(Vector3D d){
  dir = d;
  dir.normalize();
}

void
Directional::set_direction(float x, float y, float z){
  dir.x = x;
  dir.y = y;
  dir.z = z;
  dir.normalize();
}

Vector3D
Directional::get_direction(void){
  return dir;
}

RGBColor
Directional::L(ShadeRec& sr){
  return(ls * color);
}
