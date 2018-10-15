#include "AmbientOccluder.h"



AmbientOccluder::AmbientOccluder(void)
  : 	Light(),
		ls(1.0),
		color(1.0),
    min_amount(RGBColor(0.1, 0.1, 0.1))
{}

AmbientOccluder::~AmbientOccluder(void){
}

bool
AmbientOccluder::casts_shadows(void){
  return true;
}

void
AmbientOccluder::set_sampler(Sampler* s_ptr){
  if(sampler_ptr){
    delete sampler_ptr;
    sampler_ptr = NULL;
  }
  sampler_ptr = s_ptr;
  sampler_ptr->map_samples_to_hemisphere(1);
}

Vector3D
AmbientOccluder::get_direction(ShadeRec& sr){
  Point3D sp = sampler_ptr->sample_hemisphere();
  return (sp.x*u + sp.y*v + sp.z*w);
}

bool
AmbientOccluder::in_shadow(const Ray& ray, const ShadeRec& sr){
  float t;
  int num_objects = sr.w.objects.size();

  for(int j = 0; j < num_objects; j++){
    if(sr.w.objects[j]->shadow_hit(ray, t))
      return true;
  }
  return false;
}

RGBColor
AmbientOccluder::L(ShadeRec& sr){
  w = sr.normal;

  v = w ^ Vector3D(0.0072, 1.0, 0.0034);  //values from book
  v.normalize();
  u = v ^ w;

  Ray shadow_ray;
  shadow_ray.o = sr.hit_point;
  shadow_ray.d = get_direction(sr);

  if(in_shadow(shadow_ray, sr)){
    return (min_amount * ls * color);
  }else{
    return (ls * color);
  }

}
