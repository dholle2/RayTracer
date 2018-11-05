#include "../Utilities/Constants.h"
#include "Triangle.h"
#include "../Utilities/Maths.h"
#include <iostream>

using namespace std;

Triangle::Triangle (void)
	: 	GeometricObject(),
		p1(0, 0, 0),
		p2(0,0,1),
		p3(1,0,0),
		normal(0, 1, 0)
{}
  Triangle::Triangle (const Point3D& a, const Point3D& b, const Point3D& c)
  	: 	GeometricObject(),
  		p1(a),
  		p2(b),
  		p3(c)
  {
  	compute_normal();
  }
  Triangle::~Triangle (void)
  {}

  void
  Triangle::compute_normal(void) {
  	normal = (p2 - p1) ^ (p3 - p1);
  	normal.normalize();
  }

	Normal
	Triangle::get_normal(void){
		normal = Normal();
		normal.normalize();
		return normal;
	}


	Triangle*
	Triangle::clone(void) const {
		return (new Triangle(*this));
	}


  bool
  Triangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
  	double a = p1.x - p2.x, b = p1.x - p3.x, c = ray.d.x, d = p1.x - ray.o.x;
  	double e = p1.y - p2.y, f = p1.y - p3.y, g = ray.d.y, h = p1.y - ray.o.y;
  	double i = p1.z - p2.z, j = p1.z - p3.z, k = ray.d.z, l = p1.z - ray.o.z;

  	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
  	double q = g * i - e * k, s = e * j - f * i;

  	double inv_denom  = 1.0 / (a * m + b * q + c * s);

  	double e1 = d * m - b * n - c * p;
  	double beta = e1 * inv_denom;

  	if (beta < 0.0)
  	 	return (false);

  	double r = e * l - h * i;
  	double e2 = a * n + d * q + c * r;
  	double gamma = e2 * inv_denom;

  	if (gamma < 0.0 )
  	 	return (false);

  	if (beta + gamma > 1.0)
  		return (false);

  	double e3 = a * p - b * r + d * s;
  	double t = e3 * inv_denom;

  	if (t < kEpsilon)
  		return (false);
    else{
    	tmin 	= t;
    	sr.normal = normal;
    	sr.local_hit_point 	= ray.o + t * ray.d;

    	return (true);
    }
  }

	bool
	Triangle::shadow_hit(const Ray& ray, float& tmin){
		double a = p1.x - p2.x, b = p1.x - p3.x, c = ray.d.x, d = p1.x - ray.o.x;
  	double e = p1.y - p2.y, f = p1.y - p3.y, g = ray.d.y, h = p1.y - ray.o.y;
  	double i = p1.z - p2.z, j = p1.z - p3.z, k = ray.d.z, l = p1.z - ray.o.z;

  	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
  	double q = g * i - e * k, s = e * j - f * i;

  	double inv_denom  = 1.0 / (a * m + b * q + c * s);

  	double e1 = d * m - b * n - c * p;
  	double beta = e1 * inv_denom;

  	if (beta < 0.0)
  	 	return (false);

  	double r = e * l - h * i;
  	double e2 = a * n + d * q + c * r;
  	double gamma = e2 * inv_denom;

  	if (gamma < 0.0 )
  	 	return (false);

  	if (beta + gamma > 1.0)
  		return (false);

  	double e3 = a * p - b * r + d * s;
  	double t = e3 * inv_denom;

  	if (t < kEpsilon)
  		return (false);
    else{
    	tmin 	= t;
    	return (true);
    }
	}

	BBox
	Triangle::get_bounding_box(void) {
		double delta = 0.0001;  // to avoid degenerate bounding boxes

		return(BBox(min(min(p1.x, p2.x), p3.x) - delta, max(max(p1.x, p2.x), p3.x) + delta,
					min(min(p1.y, p2.y), p3.y) - delta, max(max(p1.y, p2.y), p3.y) + delta,
					min(min(p1.z, p2.z), p3.z) - delta, max(max(p1.z, p2.z), p3.z) + delta));
	}
