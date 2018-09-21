#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

#include <math.h>

#include "Constants.h"
#include "BBox.h"
#include "RGBColor.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Normal.h"
#include "Ray.h"
#include "ShadeRec.h"

class Material;

class GeometricObject{
  public:
        //constructors
    GeometricObject(void);
    GeometricObject(const GeometricObject& object);
    virtual ~GeometricObject(void);
    virtual bool hit(const Ray& ray, double& t, ShadeRec& s);

    virtual void add_object(GeometricObject* object_ptr);

  protected:
    RGBColor color;

}
