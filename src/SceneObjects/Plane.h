#ifndef __PLANE__
#define __PLANE__


#include "GeometricObject.h"

class Plane: public GeometricObject{
  public:

    Plane(void);
    Plane(const Point3D& p, const Normal& n);
//    Plane(const Point3D& p, double x, double y, double z);
    virtual bool
    hit(const Ray& ray, double& t, ShadeRec& s) const;

    virtual Plane*
    clone(void) const;

    virtual bool
    shadow_hit(const Ray& ray, float& tmin);

//    virtual BBox
//    get_bounding_box(void);

  private:

    Point3D point;  //point plane passes
    Normal  normal; //plane normal
    static const double kEpsilon;
};

#endif
