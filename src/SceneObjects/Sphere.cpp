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

  Sphere*
  Sphere::clone(void) const {
  	return (new Sphere(*this));
  }

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

  double
  Sphere::get_radius(){
    return radius;
  }

  Point3D
  Sphere::get_center(){
    return center;
  }

  bool
  Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
  	double 		t;
//    cout << "ox " << ray.o.x << " oy " << ray.o.y << " oz " << ray.o.z << " " << ray.d.x << ray.d.y << ray.d.z << endl;
//    cout << "SPHERE: x " << center.x << " y " << center.y << " z " << center.z << " <- center radius -> ";
//    cout << radius << endl;
  	Vector3D	temp 	= ray.o - center;
  	double 		a 		= ray.d * ray.d;
  	double 		b 		= 2.0 * temp * ray.d;ray.o.x == sr.local_hit_point.x &&
  	double 		c 		= temp * temp - radius * radius;
  	double 		disc	= b * b - 4.0 * a * c;

  	if (disc < 0.0){
  //              cout << "MISS!!" << endl;
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
    //              cout << "HIT!!" << endl;
  			return (true);
  		}

  		t = (-b + e) / denom;    // larger root

  		if (t > kEpsilon) {
  			tmin = t;
  			sr.normal   = (temp + t * ray.d) / radius;
  			sr.local_hit_point = ray.o + t * ray.d;
      //            cout << "HIT!!" << endl;
  			return (true);
  		}
  	}
        //  cout << "MISS!!" << endl;
  	return (false);
  }

  bool
  Sphere::hitTwice(const Ray& ray, double& tmin, ShadeRec& sr) const{
    double 		t;
  	Vector3D	temp 	= ray.o - center;
  	double 		a 		= ray.d * ray.d;
  	double 		b 		= 2.0 * temp * ray.d;
  	double 		c 		= temp * temp - radius * radius;
  	double 		disc	= b * b - 4.0 * a * c;

  	if (disc < 0.0){
  //              cout << "MISS!!" << endl;
      return(false);
    }
  	else {
  		double e = sqrt(disc);
  		double denom = 2.0 * a;
  		t = (-b - e) / denom;    // smaller root

  		if (t > kEpsilon) {
  			tmin = t;
  			//sr.normal 	 = (temp + t * ray.d) / radius;
  			//sr.local_hit_point = ray.o + t * ray.d;
        Point3D hitOne = ray.o + t * ray.d;
        Ray newRay = Ray(hitOne, ray.d);
        if(ray.o.x == sr.local_hit_point.x && ray.o.y == sr.local_hit_point.y && ray.o.z == sr.local_hit_point.z){
//          cout << "aHA! intersecting with wrong point!" << endl;
        }
        bool outHit = hit(newRay, tmin, sr);
    //              cout << "HIT!!" << endl;
  			return (true);
  		}

  		t = (-b + e) / denom;    // larger root

  		if (t > kEpsilon) {
        tmin = t;
  			//sr.normal 	 = (temp + t * ray.d) / radius;
  			//sr.local_hit_point = ray.o + t * ray.d;
        Point3D hitOne = ray.o + t * ray.d;
        Ray newRay = Ray(hitOne, ray.d);
        bool outHit = hit(newRay, tmin, sr);
    //              cout << "HIT!!" << endl;
  			return (true);
  		}
  	}
        //  cout << "MISS!!" << endl;
  	return (false);
  }//end hitTwice

  bool
  Sphere::shadow_hit(const Ray& ray, float& tmin){
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
        return (true);
      }

      t = (-b + e) / denom;    // larger root

      if (t > kEpsilon) {
        tmin = t;
        return (true);
      }
    }
    return (false);
  }

  BBox
  Sphere::get_bounding_box(void) {
    double delta = 0.0000;  // to avoid degenerate bounding boxes

    return(BBox(center.x - radius - delta, center.x + radius + delta,
          center.y - radius - delta, center.y + radius + delta,
         center.z - radius - delta, center.z + radius + delta));
  }
