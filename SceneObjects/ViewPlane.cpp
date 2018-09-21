#include ViewPlane.h

void
set_hres(int h){
  hres = h;
}

void
set_hres(int v){
  vres = v;
}

void
set_s(float size){
  s = size;
}

void
set_gamma(float g){
  gamma = g;
  inv_gamma = (1/g);
}
