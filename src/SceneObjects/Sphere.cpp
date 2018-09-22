#include "Sphere.h"
#include "math.h"
#include <iostream>

using namespace std;

const double Sphere::kEpsilon = .001;

  Sphere::Sphere(void)
  : GeometricObject(),
  center(0.0),
  radius(100.0)
  {}

  Sphere::Sphere(Point3D c, double r)
  	: 	GeometricObject(),
  		center(c),
  		radius(r)
  {}

  Sphere::~Sphere(void)
  {}


  void
  Sphere::set_center(const double x, const double y, const double z){
    center = Point3D(x, y, z);
  }

  void
  Sphere::set_center(const Point3D& c){
    center = c;
  }

  void
  Sphere::set_radius(const double r){
    radius = r;
  }





  bool
  Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
  	double 		t;
  	Vector3D	temp 	= ray.o - center;
  	double 		a 		= ray.d * ray.d;
  	double 		b 		= 2.0 * temp * ray.d;
  	double 		c 		= temp * temp - radius * radius;
  	double 		disc	= b * b - 4.0 * a * c;

  	if (disc < 0.0){
      return(false);
    }
  	else {
  		double e = sqrt(disc);
  		double denom = 2.0 * a;
  		t = (-b - e) / denom;    // smaller root

  		if (t > kEpsilon) {
  			tmin = t;
  			sr.normal 	 = (temp + t * ray.d) / radius;
  			sr.local_hit_point = ray.o + t * ray.d;
  			return (true);
  		}

  		t = (-b + e) / denom;    // larger root

  		if (t > kEpsilon) {
  			tmin = t;
  			sr.normal   = (temp + t * ray.d) / radius;
  			sr.local_hit_point = ray.o + t * ray.d;
  			return (true);
  		}
  	}

  	return (false);
  }
