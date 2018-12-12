#include "FBmTexture.h"
#include <iostream>
#include "Maths.h"
#include <math.h>
using namespace std;

  FBmTexture::FBmTexture(void)
  {
    min_value = 1;
    max_value = 5;
  }

  FBmTexture::~FBmTexture(void)
  {}

/*
  FBmTexture*
  FBmTexture::clone(void) const {
  	return (new FBmTexture(*this));
  }
*/

void
FBmTexture::set_noise(LatticeNoise* noise){
  noise_ptr = noise;
}

void
FBmTexture::set_min(float min){
  min_value = min;
}

void
FBmTexture::set_max(float max){
  max_value = max;
}

void
FBmTexture::set_color(RGBColor c1){
  color = c1;
}

RGBColor
FBmTexture::get_color(const ShadeRec& sr){
  float value = noise_ptr->value_fbm(sr.local_hit_point);
  value = min_value + (max_value - min_value) * value;

  return (value*color);
}
