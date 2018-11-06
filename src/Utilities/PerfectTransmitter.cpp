// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Constants.h"
#include "PerfectTransmitter.h"

// ---------------------------------------------------------- default constructor

PerfectTransmitter::PerfectTransmitter(void)
{}

/*
// ---------------------------------------------------------- copy constructor

PerfectTransmitter::PerfectTransmitter (const PerfectTransmitter& PerfectTransmitter) {
}



// --------------------------------------------------------------- assignment operator

PerfectTransmitter&
PerfectTransmitter::operator= (const PerfectTransmitter& rhs) {
	return (*this);
}


*/
// ---------------------------------------------------------- destructor

PerfectTransmitter::~PerfectTransmitter(void) {
}



RGBColor
PerfectTransmitter::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) {
	Normal n(sr.normal);
  float cos_theta_i = n* wo;
  float eta = ior;

  if(cos_theta_i < 0.0){
    cos_theta_i = -cos_theta_i;
    n = -n;
    eta = 1.0 / eta;
  }

  float temp = 1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta);
  float cos_theta_2 = sqrt(temp);
  wi = -wo / eta - (cos_theta_2 - cos_theta_i / eta) * n;

  return (kt / (eta * eta) * white / fabs(sr.normal * wi));
}


RGBColor
PerfectTransmitter::f(const ShadeRec& sr, const Vector3D& wo) {
	return (black);
}

bool
PerfectTransmitter::tir(const ShadeRec& sr) {
  Vector3D wo(-sr.ray.d);
  float cos_theta_i = sr.normal * wo;
  float eta = ior;

  if(cos_theta_i < 0.0){
    eta = 1.0 / eta;
  }
  return (1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta) < 0.0);

}

RGBColor
PerfectTransmitter::rho(const ShadeRec& sr, const Vector3D& wo) {
	return (black);
}
