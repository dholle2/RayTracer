#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include <string>
#include "ViewPlane.h"
#include "../Utilities/RGBColor.h"
#include "GeometricObject.h"
#include "../Misc./Tracer.h"
//#include "../Misc./BuildRedSphere.h"

using namespace std;
class World{

  public:

    World();

    ViewPlane vp;
    RGBColor background_color;
    Tracer* tracer_ptr;
    vector<GeometricObject*> objects;
    vector<RGBColor> pixels;

    void
    add_object(GeometricObject* object_ptr);

    ShadeRec
    hit_bare_bones_objects(const Ray& ray);

    void
    build(void);

    void
    render_scene(void);

    void
    open_window(const int hres, const int vres) const;

    void
    display_pixel(const int row,
      const int column,
      const RGBColor& pixel_color);
      void save_image(const string& outputFile) const;
};


#endif
