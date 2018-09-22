#include "Plane.h"
//others inherited
  const double Plane::kEpsilon = .001;

  Plane::Plane(void)
  : GeometricObject(),
  point(0.0),
  normal(0,1,0)
  {}

  Plane::Plane(const Point3D& p, const Normal& n)
  : GeometricObject(),
  point(point),
  normal(normal)
  {
    normal.normalize();
  }

  bool
  Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const{
    double t = ( (point - ray.o) * normal) / (ray.d * normal);

    if(t > kEpsilon){
      tmin = t;
      sr.normal = normal;
      sr.local_hit_point = ray.o + t* ray.d;
      return true;
    }else{
      return false;
    }
  }//end hit
