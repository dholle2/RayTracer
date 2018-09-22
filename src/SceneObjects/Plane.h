#ifndef __PLANE__
#define __PLANE__


#include "GeometricObject.h"

class Plane: public GeometricObject{
  public:

    Plane(void);
    Plane(const Point3D& p, const Normal& n);
    virtual bool
    hit(const Ray& ray, double& t, ShadeRec& s) const;

  private:

    Point3D point;  //point plane passes

    Normal  normal; //plane normal
    static const double kEpsilon;
};

#endif
