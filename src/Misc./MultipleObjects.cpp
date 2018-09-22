#include "MultipleObjects.h"
#include "../SceneObjects/World.h"

#include <iostream>

using namespace std;

MultipleObjects::MultipleObjects(void)
	: Tracer()
{}

	MultipleObjects::MultipleObjects(World* world_ptr)
		: Tracer(world_ptr)
	{}

MultipleObjects::~MultipleObjects(void)
{}

RGBColor
MultipleObjects::trace_ray(const Ray& ray) const {
	ShadeRec sr(world_ptr->hit_bare_bones_objects(ray));

	if (sr.hit_an_object){
		cout << "HIT!!" << endl;
		return (sr.color);
	}
	else{
		return (world_ptr->background_color);
	}
}
