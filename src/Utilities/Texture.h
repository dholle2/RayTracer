#ifndef __TEXTURE__
#define __TEXTURE__


#include "ShadeRec.h"


class Texture {

	public:
    Texture(void);

    virtual
    ~Texture(void);
/*
		virtual Texture*
	  clone(void) const;
*/
virtual RGBColor&
get_color(const ShadeRec& sr) = 0;

};


#endif
