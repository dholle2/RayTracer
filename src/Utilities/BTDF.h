#ifndef __BTDF__
#define __BTDF__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// BTDF is the base class for the BTDFs
// we need a sampler here, because even a Matte material needs to call sample_f with a
// cosine distribution for path shading.

//#include <math.h>

#include "RGBColor.h"
#include "Vector3D.h"
#include "ShadeRec.h"
#include "../Misc./Sampler.h"

class BTDF {
	public:

		BTDF(void);
/*
		BTDF(const BTDF& BTDF);

		virtual BTDF*
		clone(void)const = 0;

		BTDF&
		operator= (const BTDF& rhs);
*/
		virtual
		~BTDF(void);


    virtual RGBColor
    sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi)=0;

    virtual RGBColor
    f(const ShadeRec& sr, const Vector3D& wo) = 0;

    virtual bool
    tir(const ShadeRec& sr) = 0;

    virtual RGBColor
    rho(const ShadeRec& sr, const Vector3D& wo) = 0;
};

#endif
