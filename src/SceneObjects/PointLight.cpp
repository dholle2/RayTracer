// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.
/*

#include "Pointlight.h"

// ---------------------------------------------------------------- default constructor

Pointlight::Pointlight(void)
	: 	Light(),
		object_ptr(NULL),
		material_ptr(NULL)
{}


// ---------------------------------------------------------------- copy constructor

Pointlight::Pointlight(const Pointlight& al)
	: 	Light(al) {
	if(al.object_ptr)
		object_ptr = al.object_ptr->clone();
	else  object_ptr = NULL;

	if(al.material_ptr)
		material_ptr = al.material_ptr->clone();
	else  material_ptr = NULL;
}


// ---------------------------------------------------------------- clone

Pointlight*
Pointlight::clone(void) {
	return (new Pointlight(*this));
}


// ---------------------------------------------------------------- destructor

Pointlight::~Pointlight(void) {
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

Pointlight&
Pointlight::operator= (const Pointlight& rhs) {
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


// --------------------------------------------------------------- get_direction

Vector3D
Pointlight::get_direction(ShadeRec& sr) {
	sample_point = object_ptr->sample();    // used in the G function
	light_normal = object_ptr->get_normal(sample_point);
	wi = sample_point - sr.hit_point;  		// used in the G function
	wi.normalize();

	return (wi);
}


// --------------------------------------------------------------- L

RGBColor
Pointlight::L(ShadeRec& sr) {
	float ndotd = -light_normal * wi;

	if (ndotd > 0.0)
		return (material_ptr->get_Le(sr));
	else
		return (black);
}


// ---------------------------------------------------------------- in_shadow

bool
Pointlight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	float t;
	int num_objects = sr.w.objects.size();
	float ts = (sample_point - ray.o) * ray.d;

	for (int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < ts)
			return (true);

	return (false);
}


// ---------------------------------------------------------------- G
// G is part of the geometric factor

float
Pointlight::G(const ShadeRec& sr) const {
	float ndotd = -light_normal * wi;
	float d2 	= sample_point.d_squared(sr.hit_point);

	return (ndotd / d2);
}


// ---------------------------------------------------------------- pdf

float
Pointlight::pdf(const ShadeRec& sr) const {
	return (object_ptr->pdf(sr));
}

*/
