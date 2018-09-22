#include "GeometricObject.h"


  GeometricObject::GeometricObject(void)
  : color(black)
  {}

  GeometricObject::GeometricObject(const GeometricObject& object)
  : color(object.color)
  {}

  GeometricObject::~GeometricObject(void)
  {}

  void
  GeometricObject::add_object(GeometricObject* object_ptr)
  {}

  RGBColor
  GeometricObject::get_color(void){
    return color;
  }

  bool
  GeometricObject::hit(const Ray& ray, double& tmin, ShadeRec& sr) const{
      return true;
  }//end hit

  void
  GeometricObject::set_color(float x, float y, float z){
    color = RGBColor(x, y, z);
  }
