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

		virtual bool
		casts_shadows(void) = 0;

		virtual bool
	  in_shadow(const Ray& ray, const ShadeRec& sr) = 0;

		virtual RGBColor
		L(ShadeRec& sr);

		virtual float
		G(const ShadeRec& sr) const;

		virtual float
		pdf(const ShadeRec& sr) const;
  };

  #endif
