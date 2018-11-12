#ifndef __Emissive__
#define __Emissive__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Material.h"
#include "Lambertian.h"

//----------------------------------------------------------------------------- class Emissive

class Emissive: public Material {
	public:

		Emissive(void);

		Emissive(const Emissive& m);

		virtual Material*
		clone(void) const;

		Emissive&
		operator= (const Emissive& rhs);

//		~Emissive(void);

    float ls;     //radiance scaling
    RGBColor ce;  //color

		void
		scale_radiance(const float k);

		void
		set_ce(const float r, const float g, const float b);

		void
		set_ce(RGBColor rgb);

		virtual RGBColor
		get_Le(ShadeRec& sr);

		virtual RGBColor
		area_light_shade(ShadeRec& sr);

		virtual RGBColor
		shade(ShadeRec& sr);

};


inline void
Emissive::scale_radiance(const float k) {
	ls = k;
}

inline void
Emissive::set_ce(const float r, const float g, const float b) {
	ce = RGBColor(r,g,b);
}

inline void
Emissive::set_ce(RGBColor rgb) {
	ce = rgb;
}

// ---------------------------------------------------------------- set_cd

inline RGBColor
Emissive::get_Le(ShadeRec& sr) {
  return ce * ls;
}

#endif
