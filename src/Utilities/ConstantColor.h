#ifndef __CONSTANTCOLOR__
#define __CONSTANTCOLOR__


#include "ShadeRec.h"
#include "Texture.h"

class ConstantColor: public Texture {

	public:
    ConstantColor(void);

    virtual
    ~ConstantColor(void);
/*
		virtual constantColor*
	  clone(void) const;
*/

void
set_color(RGBColor& c);

virtual RGBColor
get_color(const ShadeRec& sr);

private:
		RGBColor color;

};


#endif
