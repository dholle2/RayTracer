#include "Light.h"
#include "../Utilities/Constants.h"

Light::Light(void)
{}
Light::~Light(void)
{}

RGBColor
Light::L(ShadeRec& s) {
	return (black);
}
