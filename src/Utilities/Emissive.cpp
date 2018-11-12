// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.
#include <iostream>


#include "Emissive.h"
using namespace std;
// ---------------------------------------------------------------- default constructor

Emissive::Emissive (void)
	:	Material(),
		ls(0.5),
		ce(1.0, 1.0, 1.0)
{}



// ---------------------------------------------------------------- copy constructor

Emissive::Emissive(const Emissive& m)
	: 	Material(m)
{
}


// ---------------------------------------------------------------- clone

Material*
Emissive::clone(void) const {
	return (new Emissive(*this));
}


// ---------------------------------------------------------------- assignment operator

Emissive&
Emissive::operator= (const Emissive& rhs) {
/*
	if (this == &rhs)
		return (*this);

	Material::operator=(rhs);

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if (rhs.diffuse_brdf)
		diffuse_brdf = rhs.diffuse_brdf->clone();
*/
	return (*this);
}


// ---------------------------------------------------------------- destructor
/*
Emissive::~Emissive(void) {

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
}

*/
// ---------------------------------------------------------------- shade

RGBColor
Emissive::shade(ShadeRec& sr) {
  if (-sr.normal * sr.ray.d > 0.0){
    return (ls * ce);
  }else{
		cout << "wrong side" << endl;
    return (RGBColor(1,0,0));
  }

  /*
//	cout << "Starting Emissive Shading" << endl;
	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights	= sr.w.lights.size();

//	cout << "Ambient Color: " << L.r << " " << L.g << " " << L.b << endl;


	for (int j = 0; j < num_lights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = sr.normal * wi;



		if (ndotwi > 0.0){

	    bool in_shadow = false;

			if(sr.w.lights[j]->casts_shadows()){
	      Ray shadowRay(sr.hit_point, wi);
	      in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
	    }

			if(!in_shadow){
				L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
			}
		}
	}
//	cout << "Final Color: " << L.r << " " << L.g << " " << L.b << endl;
	return (L);
*/
}

RGBColor
Emissive::area_light_shade(ShadeRec& sr){
  if (-sr.normal * sr.ray.d > 0.0){
    return (ls * ce);
  }else{
    return (black);
  }
}
