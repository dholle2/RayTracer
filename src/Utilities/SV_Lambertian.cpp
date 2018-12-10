
#include "SV_Lambertian.h"
#include "Constants.h"
#include <iostream>

using namespace std;
// ---------------------------------------------------------------------- default constructor

SV_Lambertian::SV_Lambertian(void)
	:   BRDF(),
		kd(0.0),
		cd()
{}


// ---------------------------------------------------------------------- copy constructor

SV_Lambertian::SV_Lambertian(const SV_Lambertian& lamb)
{}


// ---------------------------------------------------------------------- assignment operator

SV_Lambertian&
SV_Lambertian::operator= (const SV_Lambertian& rhs) {
return *this;
}


// ---------------------------------------------------------------------- destructor

SV_Lambertian::~SV_Lambertian(void) {}


// ---------------------------------------------------------------------- clone

SV_Lambertian*
SV_Lambertian::clone(void) const {
	return (new SV_Lambertian(*this));
}



RGBColor
SV_Lambertian::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	return (kd * cd->get_color(sr) * invPI);
}

// ---------------------------------------------------------------------- sample_f

// this generates a direction by sampling the hemisphere with a cosine distribution
// this is called in path_shade for any material with a diffuse shading component
// the samples have to be stored with a cosine distribution

RGBColor
SV_Lambertian::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {

	Vector3D w = sr.normal;
	Vector3D v = Vector3D(0.0034, 1, 0.0071) ^ w;
	v.normalize();
	Vector3D u = v ^ w;

	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;
	wi.normalize();

	pdf = sr.normal * wi * invPI;

	return (kd * cd->get_color(sr) * invPI);
}



// ---------------------------------------------------------------------- rho

RGBColor
SV_Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const {
//	cout << "MADE IT TO RHO" << endl;
//	cout << "KD: " << kd << endl;
	return (kd * cd->get_color(sr));
}

void
SV_Lambertian::set_kd(const float k){
  kd = k;
}

void
SV_Lambertian::set_cd(Texture* c){
  cd = c;
}
