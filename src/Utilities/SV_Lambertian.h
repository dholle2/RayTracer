
#ifndef __SV_LAMBERTIAN__
#define __SV_LAMBERTIAN__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This implements a perfect diffuse scatterer

#include "BRDF.h"
#include "Texture.h"

class SV_Lambertian: public BRDF
{
	public:

		SV_Lambertian(void);

		SV_Lambertian(const SV_Lambertian& lamb);

		SV_Lambertian&
		operator= (const SV_Lambertian& rhs);

		virtual
		~SV_Lambertian(void);

		virtual SV_Lambertian*
		clone(void) const;

		virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

		virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

		virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;

    void
		set_kd(const float k);

		void
		set_cd(Texture* c);

private:

  float kd;
  Texture* cd;
};

#endif
