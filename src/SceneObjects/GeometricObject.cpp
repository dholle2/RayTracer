#include "GeometricObject.h"


  GeometricObject::GeometricObject(void)
  : color(black)
  {}

  GeometricObject::GeometricObject(const GeometricObject& object)
  : color(object.color)
  {}
/*
    GeometricObject*
    GeometricObject::clone(void) const{
      	return (new GeometricObject(*this));
    }
*/


  Material*
  GeometricObject::get_material(void) const{
  	return (material_ptr);
  }


  void
  GeometricObject::set_material(Material* m) {
  	material_ptr = m;
  }

  GeometricObject*
  GeometricObject::clone(void) const {
  	return (new GeometricObject(*this));
  }

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

  bool
  GeometricObject::shadow_hit(const Ray& ray, float& tmin){
    return false;
  }

  BBox
  GeometricObject::get_bounding_box(void){
    bbox = BBox();
    return bbox;
  }

    Normal
    GeometricObject::get_normal(void){
      normal = Normal();
      return normal;
    }
