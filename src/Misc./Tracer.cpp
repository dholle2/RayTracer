#include "Tracer.h"
#include <iostream>

using namespace std;

Tracer::Tracer(void)
	: world_ptr(NULL)
{}

Tracer::Tracer(World* _worldPtr)
	: world_ptr(_worldPtr)
{}

Tracer::~Tracer(void){
	if (world_ptr)
		world_ptr = NULL;
}

RGBColor
Tracer::trace_ray(const Ray& ray) const{
	return white;
}
//	RayCast
RGBColor
Tracer::trace_ray(const Ray ray, const int depth){
	return white;
}

void
Tracer::kill(void){
	cout << "Tracer" << endl;
}
