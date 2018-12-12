#ifndef __FBMTEXTURE__
#define __FBMTEXTURE__


#include "ShadeRec.h"
#include "Texture.h"
#include "LatticeNoise.h"

class FBmTexture: public Texture {

	public:
    FBmTexture(void);

    virtual
    ~FBmTexture(void);
/*
		virtual FBmTexture*
	  clone(void) const;
*/

void
set_color(RGBColor& c1, RGBColor& c2, RGBColor& c3);

void
set_noise(LatticeNoise* noise);

void
set_min(float min);

void
set_max(float max);

void
set_color(RGBColor c1);

virtual RGBColor
get_color(const ShadeRec& sr);

private:
		RGBColor color;
    LatticeNoise* noise_ptr;
    float min_value, max_value;;
};


#endif
