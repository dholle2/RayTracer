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
#include "../Utilities/BBox.h"
#include "../Utilities/Normal.h"

class Material;

class GeometricObject{
  public:


    Material*
		get_material(void) const;

    void
    set_material(Material* m);


    virtual GeometricObject*
		clone(void) const;

//constructors
    GeometricObject(void);
    GeometricObject(const GeometricObject& object);

    virtual ~GeometricObject(void);
  //  virtual bool hit(const Ray& ray, double& t, ShadeRec& s);

    virtual void add_object(GeometricObject* object_ptr);

    RGBColor get_color(void);

    virtual bool
    hit(const Ray& ray, double& t, ShadeRec& s) const;

    virtual bool
    hitTwice(const Ray& ray, double& tmin, ShadeRec& sr) const;

    virtual double
    get_radius();

    virtual Point3D
		get_center();

    void
    set_color(float x, float y, float z);

    virtual bool
    shadow_hit(const Ray& ray, float& tmin);    //for each object, same as hit without shading

    mutable Material*   material_ptr;
    RGBColor color;
    BBox bbox;
    Normal normal;

    virtual Normal
    get_normal(void);

    virtual Normal
    get_normal(const Point3D& point);

    virtual Point3D
    sample(void);

    virtual float
    pdf(const ShadeRec& sr);

    virtual BBox
    get_bounding_box(void);

};

#endif
