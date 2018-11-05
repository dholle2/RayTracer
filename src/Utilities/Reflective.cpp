// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include <iostream>

#include "Reflective.h"

using namespace std;
// ---------------------------------------------------------------- default constructor

Reflective::Reflective (void)
	:	Phong(),
		reflective_brdf(new PerfectSpecular)
{}

/*
// ---------------------------------------------------------------- copy constructor

Reflective::Reflective(const Reflective& rm)
	: 	Phong(rm) {

	if(rm.reflective_brdf)
		reflective_brdf = rm.reflective_brdf->clone();
	else
		reflective_brdf = NULL;
}


// ---------------------------------------------------------------- assignment operator

Reflective&
Reflective::operator= (const Reflective& rhs) {
	if (this == &rhs)
		return (*this);

	Phong::operator=(rhs);

	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}

	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();

	return (*this);
}
*/

// ---------------------------------------------------------------- clone

Reflective*
Reflective::clone(void) const {
	return (new Reflective(*this));
}


// ---------------------------------------------------------------- destructor
/*
Reflective::~Reflective(void) {
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
}
*/

// ------------------------------------------------------------------------------------ shade

RGBColor
Reflective::shade(ShadeRec& sr) {
//	cout << "ATTEMPTING REFLECTIVE SHADING" << endl;
	RGBColor L(Phong::shade(sr));  // direct illumination
//	cout << "Phong Color: " << L.r << L.g << L.b << endl;
	Vector3D wo = -sr.ray.d;
	Vector3D wi;
//	cout << "before fr" << endl;
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
//	cout << "after fr" << endl;
	Ray reflected_ray(sr.hit_point, wi);
//cout << "Ray reflected_ray(sr.hit_point, wi) DONE" << endl;

	//reflected_ray.depth = sr.depth + 1;		//for transparency and reflections later
// disabling this line seems to result in infinite loops

	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);
		//	cout << "Reflect Color: " << L.r << L.g << L.b << endl;
	return (L);
}
