#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include <string>
#include "ViewPlane.h"
#include "../Utilities/RGBColor.h"
#include "GeometricObject.h"
#include "../Misc./Tracer.h"
#include "Light.h"
#include "../Misc./Camera.h"
//#include "../Misc./BuildRedSphere.h"
#include "Ambient.h"
#include "Grid.h"

using namespace std;
class World{

  public:

    World();

    ViewPlane vp;
    RGBColor background_color;
    Tracer* tracer_ptr;
    vector<GeometricObject*> objects;
    vector<RGBColor> pixels;
    Light* ambient_ptr;     //light stuff
    vector<Light*> lights;
    Camera* camera_ptr;

    void
    set_camera(Camera* camera);

    void
    add_object(GeometricObject* object_ptr);

    void
    add_light(Light* light_ptr);

    void
    set_ambient_light(Light* ambient);

    ShadeRec
    hit_bare_bones_objects(const Ray& ray);

    ShadeRec
    hit_objects(const Ray& ray);

    void
    buildDiffuse(void);

    void
    buildReflective(void);

    void
    buildMirror(void);

    void
    buildAreaLight(void);

    void
    buildMesh(void);

    void
    render_scene_ortho(void);

    void
    render_scene_multijittered(void);

    void
    render_scene_perspective(void);

    void
    open_window(const int hres, const int vres) const;

    void
    display_pixel(const int row,
      const int column,
      const RGBColor& pixel_color);
      void save_image(const string& outputFile) const;

    RGBColor
    clamp_to_color(const RGBColor& raw_color);

    RGBColor
    max_to_one(const RGBColor& c);
};


#endif
