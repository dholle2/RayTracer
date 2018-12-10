#ifndef __PLANECHECKER__
#define __PLANECHECKER__


#include "ShadeRec.h"
#include "Texture.h"

class PlaneChecker: public Texture {

	public:
    PlaneChecker(void);

    virtual
    ~PlaneChecker(void);
/*
		virtual PlaneChecker*
	  clone(void) const;
*/

void
set_color(RGBColor& c1, RGBColor& c2, RGBColor& c3);

void
set_size(float s);

void
set_outline_width(float w);

virtual RGBColor&
get_color(const ShadeRec& sr);

private:
		RGBColor color1;
    RGBColor color2;
    RGBColor outline_color;
    float outline_width;
    float size;
};


#endif
