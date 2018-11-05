#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "GeometricObject.h"

class Triangle: public GeometricObject {
	public:

    Triangle(void);
    Triangle(const Point3D& a, const Point3D& b, const Point3D& c);
		~Triangle(void);

    void
    compute_normal(void);

		virtual Triangle*
	  clone(void) const;

    virtual bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		virtual bool
    shadow_hit(const Ray& ray, float& tmin);

    Point3D p1, p2, p3;
    Normal normal;

		virtual BBox
		get_bounding_box(void);

		virtual Normal
		get_normal(void);

  };

#endif
