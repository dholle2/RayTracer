#include "Directional.h"

Directional::Directional(void)
:Light(),
ls(1.0),
color(1.0),
dir(0,-1, 0)
{}

Directional::~Directional(void)
{}

  void
  Directional::set_ls(float l){
    ls = l;
  }

void
Directional::set_direction(Vector3D d){
  dir = d;
  dir.normalize();
}

void
Directional::set_direction(float x, float y, float z){
  dir.x = x;
  dir.y = y;
  dir.z = z;
  dir.normalize();
}

Vector3D
Directional::get_direction(ShadeRec& sr){
  return dir;
}

RGBColor
Directional::L(ShadeRec& sr){
  return(ls * color);
}

bool
Directional::in_shadow(const Ray& ray, const ShadeRec& sr){
  float t;
  int num_objects = sr.w.objects.size();
  //float d = location.distance(ray.o);

    for(int j = 0; j < num_objects; j++){
      if (sr.w.objects[j]->shadow_hit(ray, t) /* && t < d */){
        return true;
      }
    }
    return false;
}

bool
Directional::casts_shadows(void){
  return true;
}
