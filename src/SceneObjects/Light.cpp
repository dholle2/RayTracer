#include "Light.h"
#include "../Utilities/Constants.h"
#include <iostream>
using namespace std;

Light::Light(void)
{}
Light::~Light(void)
{}

RGBColor
Light::L(ShadeRec& s) {
	return (black);
}

float
Light::G(const ShadeRec& sr) const{
	return 1.0;
}

float
Light::pdf(const ShadeRec& sr) const{
	cout << "wrong pdf";
	return 1.0;
}
