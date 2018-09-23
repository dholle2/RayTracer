#include "RayCast.h"
#include "../SceneObjects/World.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/Material.h"

/*
RayCast::RayCast(void)
	: Tracer()
{}
RayCast::RayCast(World* _worldPtr)
	: Tracer(_worldPtr)
{}
RayCast::~RayCast(void) {}

RGBColor
RayCast::trace_ray(const Ray ray, const int depth) const {
	ShadeRec sr(world_ptr->hit_objects(ray));

	if (sr.hit_an_object) {
		sr.ray = ray;
		return (sr.material_ptr->shade(sr));
	}
	else
		return (world_ptr->background_color);
}

*/
