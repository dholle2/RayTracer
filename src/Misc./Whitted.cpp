// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.
#include <iostream>
using namespace std;

#include "Whitted.h"
#include "../SceneObjects/World.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/Material.h"

// -------------------------------------------------------------------- default constructor

Whitted::Whitted(void)
	: Tracer()
{}


// -------------------------------------------------------------------- constructor

Whitted::Whitted(World* _worldPtr)
	: Tracer(_worldPtr)
{}


// -------------------------------------------------------------------- destructor

Whitted::~Whitted(void) {}


// -------------------------------------------------------------------- trace_ray

RGBColor
Whitted::trace_ray(const Ray ray, const int depth) {
//	cout << "going whitted" << endl;
	if (depth > world_ptr->vp.max_depth){
//		cout << "depth too high" << endl;
		return(black);
	}
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));

		if (sr.hit_an_object) {
	//		cout << "HIT" << endl;
			sr.depth = depth;
			sr.ray = ray;
			return (sr.material_ptr->shade(sr));
		}
		else{
//			cout << "MISS" << endl;
			return (world_ptr->background_color);
		}
	}
}

void
Whitted::kill(void){
	cout << "whitted" << endl;
}
