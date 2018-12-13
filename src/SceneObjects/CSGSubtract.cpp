// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <vector>

#include "../Utilities/Constants.h"
#include "CSGSubtract.h"
#include <iostream>

using namespace std;

// ----------------------------------------------------------------  default constructor

CSGSubtract::CSGSubtract (void)
	: 	GeometricObject()
{}


// ---------------------------------------------------------------- clone

CSGSubtract*
CSGSubtract::clone(void) const {
	return (new CSGSubtract(*this));
}


// ---------------------------------------------------------------- copy constructor

CSGSubtract::CSGSubtract (const CSGSubtract& c)
	: GeometricObject(c) {

	copy_objects(c.objects);
}



// ---------------------------------------------------------------- assignment operator

CSGSubtract&
CSGSubtract::operator= (const CSGSubtract& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	copy_objects(rhs.objects);

	return (*this);
}


// ---------------------------------------------------------------- destructor

CSGSubtract::~CSGSubtract(void) {
	delete_objects();
}


// ---------------------------------------------------------------- add_object

void
CSGSubtract::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}


//------------------------------------------------------------------ set_material
// sets the same material on all objects

void
CSGSubtract::set_material(Material* material_ptr) {
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
		objects[j]->set_material(material_ptr);
}


//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The array still exists, because it'ss an automatic variable, but it's empty

void
CSGSubtract::delete_objects(void) {
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}

	objects.erase(objects.begin(), objects.end());
}


//------------------------------------------------------------------ copy_objects

void
CSGSubtract::copy_objects(const vector<GeometricObject*>& rhs_ojects) {
	delete_objects();
	int num_objects = rhs_ojects.size();

	for (int j = 0; j < num_objects; j++)
		objects.push_back(rhs_ojects[j]->clone());
}


//------------------------------------------------------------------ hit

bool
CSGSubtract::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double		t;
	Normal		normal;
	Point3D		local_hit_point;
	bool		hit 		= false;
				tmin 		= kHugeValue;
	int 		num_objects	= objects.size();
//	cout << "BEFORE HIT CALCULATED: " << num_objects << endl;

//	for (int j = 0; j < num_objects; j++)
		if (objects[0]->hit(ray, t, sr)&& (t < tmin)) {
			hit				= true;
			tmin 			= t;
			material_ptr	= objects[0]->get_material();	// lhs is GeometricObject::material_ptr
			normal			= sr.normal;
			local_hit_point	= sr.local_hit_point;
		}else if(objects[1]->hitTwice(ray, t, sr) && (t < tmin)){
			double x1, y1, z1, x2, y2, z2;
			x1 = sr.local_hit_point.x;
			y1 = sr.local_hit_point.y;
			z1 = sr.local_hit_point.z;
			x2 = objects[0]->get_center().x;
			y2 = objects[0]->get_center().y;
			z2 = objects[0]->get_center().z;
			double x, y, z;
			x = x1-x2;
			y = y1-y2;
			z = z1-z2;
			x*=x;
			y*=y;
			z*=z;
			double distance = x+y+z;
			distance = sqrt(distance);
//			cout << "Result: " << result << endl;
			if(distance < objects[1]->get_radius()) {
				hit				= true;
				tmin 			= t;
				material_ptr	= objects[1]->get_material();	// lhs is GeometricObject::material_ptr
				normal			= sr.normal;
				local_hit_point	= sr.local_hit_point;
			}

		}

	if (hit) {
		sr.t				= tmin;
		sr.normal 			= normal;
		sr.local_hit_point 	= local_hit_point;
	}
//	cout << "BEFORE HIT RETURNED: " << hit << endl;
	return (hit);
}

bool
CSGSubtract::shadow_hit(const Ray& ray, float& tmin){
	float		t;
	Normal		normal;
	Point3D		local_hit_point;
	bool		hit 		= false;
				tmin 		= kHugeValue;
	int 		num_objects	= objects.size();
//	cout << num_objects << endl;

	for (int j = 0; j < num_objects; j++){
		if (objects[j]->shadow_hit(ray, t) && (t < tmin)) {
//			cout << "SHADOW HIT" << endl;
			hit				= true;
			tmin 			= t;
			material_ptr	= objects[j]->get_material();	// lhs is GeometricObject::material_ptr
//			cout << j << endl;
		}
//		cout << j << endl;
	}
//cout << "SHADOW MISS" << endl;
	return hit;
}
