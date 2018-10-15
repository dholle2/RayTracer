#include "RayCast.h"
#include "../SceneObjects/World.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/Material.h"
#include <iostream>

using namespace std;

RayCast::RayCast(void)
	: Tracer()
{}
RayCast::RayCast(World* _worldPtr)
	: Tracer(_worldPtr)
{}
RayCast::~RayCast(void) {}

RGBColor
RayCast::trace_ray(const Ray ray, const int depth)  {

//	cout << "starting trace ray!" << endl;
	ShadeRec sr(world_ptr->hit_objects(ray));
//	cout << "shade rec set, sir!" << endl;

	if (sr.hit_an_object) {
//		cout << "HIT" << endl;
		sr.ray = ray;
//		cout << "sr.ray = ray done!" << endl;
		if(sr.material_ptr != NULL){
			return (sr.material_ptr->shade(sr));
		}else
			return red;
	}
	else
		return (world_ptr->background_color);
}
