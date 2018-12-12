#include "ConstantColor.h"
#include <iostream>

using namespace std;

  ConstantColor::ConstantColor(void)
  {}

  ConstantColor::~ConstantColor(void)
  {}

/*
  constantColor*
  constantColor::clone(void) const {
  	return (new constantColor(*this));
  }
*/


void
ConstantColor::set_color(RGBColor& c){
  color = c;

}

RGBColor
ConstantColor::get_color(const ShadeRec& sr){
  return color;

}
