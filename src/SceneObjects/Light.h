#ifndef __LIGHT__
#define __LIGHT__

#include "../Utilities/Vector3D.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"

class ShadeRec;


class Light {
	public:

		Light(void);
    virtual
		~Light(void);

    virtual Vector3D
		get_direction(ShadeRec& sr) = 0;

		virtual RGBColor
		L(ShadeRec& sr);
  };

  #endif
