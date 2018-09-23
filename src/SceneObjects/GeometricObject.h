#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

#include <math.h>

#include "../Utilities/Constants.h"
#include "../Utilities/BBox.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"

class Material;

class GeometricObject{
  public:
        //constructors

    Material*
		get_material(void);
    void
    set_material(Material m);
    
    GeometricObject(void);
    GeometricObject(const GeometricObject& object);
    virtual ~GeometricObject(void);
  //  virtual bool hit(const Ray& ray, double& t, ShadeRec& s);

    virtual void add_object(GeometricObject* object_ptr);

    RGBColor get_color(void);

    virtual bool
    hit(const Ray& ray, double& t, ShadeRec& s) const;

    void
    set_color(float x, float y, float z);

    mutable Material*   material_ptr;
    RGBColor color;
};

#endif
