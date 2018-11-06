#ifndef __PerfectTransmitter__
#define __PerfectTransmitter__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// PerfectTransmitter is the base class for the PerfectTransmitters
// we need a sampler here, because even a Matte material needs to call sample_f with a
// cosine distribution for path shading.

//#include <math.h>

#include "RGBColor.h"
#include "Vector3D.h"
#include "ShadeRec.h"
#include "../Misc./Sampler.h"
#include "BTDF.h"

class PerfectTransmitter: public BTDF {
	public:

		PerfectTransmitter(void);
/*
		PerfectTransmitter(const PerfectTransmitter& PerfectTransmitter);

		virtual PerfectTransmitter*
		clone(void)const = 0;

		PerfectTransmitter&
		operator= (const PerfectTransmitter& rhs);
*/
		virtual
		~PerfectTransmitter(void);


    virtual RGBColor
    sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi);

    virtual RGBColor
    f(const ShadeRec& sr, const Vector3D& wo);

    virtual bool
    tir(const ShadeRec& sr);

    virtual RGBColor
    rho(const ShadeRec& sr, const Vector3D& wo);

    void
    set_kt(float k);

    void
    set_ior(float k);

    float kt;
    float ior;
};

#endif

// -------------------------------------------------------------- set_ka

inline void
PerfectTransmitter::set_kt(float k) {
	kt = k;
}



// -------------------------------------------------------------- set_kd

inline void
PerfectTransmitter::set_ior(float i) {
	ior = i;
}
