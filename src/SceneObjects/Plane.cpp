#include "Plane.h"
#include <iostream>
using namespace std;
//others inherited
  const double Plane::kEpsilon = .001;

  Plane::Plane(void)
  : GeometricObject(),
  point(0.0),
  normal(0,0,1)
  {}

  Plane::Plane(const Point3D& p, const Normal& n)
  : GeometricObject(),
  point(p),
  normal(n)
  {
  //  normal.normalize();
  }

  bool
  Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const{
    double t = (point - ray.o) * normal / (ray.d * normal);
      cout << ray.d.x << " x " << ray.d.y << " oy " << ray.d.z << " z " << endl;
      cout << "normal " << normal.x << " x " << normal.y << " y " << normal.z << " z " << endl;
      cout << "ox " << ray.o.x << " oy " << ray.o.y << " oz " << ray.o.z << " " << ray.d.x << ray.d.y << ray.d.z << endl;
      cout << "PLANE: x " << point.x << " y " << point.y << " z " << point.z << " <- center" << endl;
//        cout << radius << endl;
    if(t > kEpsilon){
      tmin = t;
      sr.normal = normal;
      sr.local_hit_point = ray.o + t* ray.d;
      cout << "HIT" << endl;
      return true;
    }else{
      cout << "MISS" << endl;
      return false;
    }
  }//end hit
