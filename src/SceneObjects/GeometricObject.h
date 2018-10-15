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
//#include "../Utilities/Material.h"

class Material;

class GeometricObject{
  public:


    Material*
		get_material(void) const;

    void
    set_material(Material* m);


//    virtual GeometricObject*
//		clone(void) const;

//constructors
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

    virtual bool
    shadow_hit(const Ray& ray, float& tmin) = 0;    //for each object, same as hit without shading

    mutable Material*   material_ptr;
    RGBColor color;
};

#endif
