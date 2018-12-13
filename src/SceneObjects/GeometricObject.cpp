#include "GeometricObject.h"
#include <iostream>
using namespace std;

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

  bool
  GeometricObject::hitTwice(const Ray& ray, double& tmin, ShadeRec& sr) const{
      cout << "taking hitTwice of non-sphere, returns false" << endl;
      return false;
  }//end hitTwice

  double
  GeometricObject::get_radius(){
    cout << "taking radius of non-sphere, returns 1" << endl;
    return 1.0;
  }

  Point3D
  GeometricObject::get_center(){
    cout << "taking center of non-sphere, returns 0,0,0" << endl;
    return Point3D(0,0,0);
  }

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

  Normal
  GeometricObject::get_normal(const Point3D& point){
//    cout << "Geo Normal" << endl;
    normal = Normal();
    return normal;
  }

  Point3D
  GeometricObject::sample(void){
    return Point3D(1,1,1);
  }

  float
  GeometricObject::pdf(const ShadeRec& sr){
  //  cout << "wrong pdf" << endl;
    return 1.0;
  }
