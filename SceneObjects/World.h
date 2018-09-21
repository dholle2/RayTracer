#ifndef __WORLD__
#define __WORLD__

#include "ViewPlane.h"
#include "RGBColor.h"
#include "Sphere.h"
#include "Tracer.h"

class world{
  public:
    ViewPlane vp;
    RGBColor background_color;
    Sphere sphere;
    Tracer* tracer_ptr;

    World(void);

    void
    build(void);

    void
    render_scene(void) const;

    void
    open_window(const int hres, const int vres) const;

    void
    display_pixel(const int row,
      const int column,
        const RGBColor& pixel_color) const;
}
