#include "ViewPlane.h"

ViewPlane::ViewPlane(void)
{
  hres = 10;
  vres = 10;
  s = 1;
  gamma = 1;
  inv_gamma = 1;
}

void
ViewPlane::set_hres(int h){
  hres = h;
}

void
ViewPlane::set_vres(int v){
  vres = v;
}

void
ViewPlane::set_s(float size){
  s = size;
}

void
ViewPlane::set_gamma(float g){
  gamma = g;
  inv_gamma = (1/g);
}
