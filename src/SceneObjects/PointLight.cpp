// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "PointLight.h"

// ---------------------------------------------------------------- default constructor

PointLight::PointLight(void)
	: 	Light(),
    ls(1.0),
    color(1.0),
    location(0,0,0)
//		object_ptr(NULL),
//		material_ptr(NULL)
{}

PointLight::PointLight(float x, float y, float z)
  :   Light(),
    ls(1.0),
    color(1.0),
    location(Point3D(x,y,z))

{}




// ---------------------------------------------------------------- copy constructor
/*
PointLight::PointLight(const PointLight& al)
	: 	Light(al) {
	if(al.object_ptr)
		object_ptr = al.object_ptr->clone();
	else  object_ptr = NULL;

	if(al.material_ptr)
		material_ptr = al.material_ptr->clone();
	else  material_ptr = NULL;
}

*/

// ---------------------------------------------------------------- clone

PointLight*
PointLight::clone(void) {
	return (new PointLight(*this));
}


// ---------------------------------------------------------------- destructor

PointLight::~PointLight(void) {
	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}

	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
}


// --------------------------------------------------------------- assignment operator
/*
PointLight&
PointLight::operator= (const PointLight& rhs) {
	if (this == &rhs)
		return (*this);

	Light::operator=(rhs);

	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}

	if (rhs.object_ptr)
		object_ptr = rhs.object_ptr->clone();

	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr->clone();

	return (*this);
}
*/

// --------------------------------------------------------------- get_direction

Vector3D
PointLight::get_direction(ShadeRec& sr) {

  return((location - sr.hit_point).hat());
  /*
	sample_point = object_ptr->sample();    // used in the G function
	light_normal = object_ptr->get_normal(sample_point);
	wi = sample_point - sr.hit_point;  		// used in the G function
	wi.normalize();

	return (wi);
  */
}


// --------------------------------------------------------------- L

RGBColor
PointLight::L(ShadeRec& sr) {
  return (ls*color);

  /*
	float ndotd = -light_normal * wi;

	if (ndotd > 0.0)
		return (material_ptr->get_Le(sr));
	else
		return (black);
  */
}


// ---------------------------------------------------------------- in_shadow

bool
PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) {
	float t;
	int num_objects = sr.w.objects.size();
	float ts = (sample_point - ray.o) * ray.d;

	for (int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < ts)
			return (true);

	return (false);
}

bool
PointLight::casts_shadows(void){
  return true;
}


// ---------------------------------------------------------------- G
// G is part of the geometric factor
/*
float
PointLight::G(const ShadeRec& sr) const {
	float ndotd = -light_normal * wi;
	float d2 	= sample_point.d_squared(sr.hit_point);

	return (ndotd / d2);
}
*/

// ---------------------------------------------------------------- pdf
/*
float
PointLight::pdf(const ShadeRec& sr) const {
	return (object_ptr->pdf(sr));
}
*/
