// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Constants.h"
#include "Transparent.h"

// ---------------------------------------------------------- default constructor

Transparent::Transparent(void)
:	Phong(),
  reflective_brdf(new PerfectSpecular),
  specular_btdf(new PerfectTransmitter)
{
}

/*
// ---------------------------------------------------------- copy constructor

Transparent::Transparent (const Transparent& Transparent) {
}



// --------------------------------------------------------------- assignment operator

Transparent&
Transparent::operator= (const Transparent& rhs) {
	return (*this);
}

*/
// ---------------------------------------------------------- destructor

Transparent::~Transparent(void) {
}

RGBColor
Transparent::shade(ShadeRec& sr){
  RGBColor L(Phong::shade(sr));

  Vector3D wo = -sr.ray.d;
  Vector3D wi;
  RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
  Ray reflected_ray(sr.hit_point, wi);

  if(specular_btdf->tir(sr)){
    L += sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
    //kr = 1.0
  }
  else{
    Vector3D wt;
    RGBColor ft = specular_btdf-> sample_f(sr, wo, wt);
    Ray transmitted_ray(sr.hit_point, wt);

    L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * fabs(sr.normal * wi);
    L += ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth + 1) * fabs(sr.normal * wt);
  }

  return (L);
}
