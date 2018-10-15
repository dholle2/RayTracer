#ifndef __SPHERE__
#define __SPHERE__


#include "GeometricObject.h"

class Sphere: public GeometricObject {

	public:
    Sphere(void);

    Sphere(Point3D c, double r);

    virtual
    ~Sphere(void);

    void
    set_center(const double x, const double y, const double z);

    void
    set_center(const Point3D& c);

    void
    set_radius(const double r);

    virtual bool
    hit(const Ray& ray, double& t, ShadeRec& s) const;

		virtual Sphere*
	  clone(void) const;

		virtual bool
		shadow_hit(const Ray& ray, float& tmin);

  private:

    Point3D center;
    double radius;

    static const double kEpsilon;
};

#endif
