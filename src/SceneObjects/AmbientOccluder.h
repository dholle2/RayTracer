#ifndef __AMBIENT_OCCLUDER__
#define __AMBIENT_OCCLUDER__

#include "Light.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/RGBColor.h"
#include "World.h"
#include "../Utilities/ShadeRec.h"
#include "../Misc./Sampler.h"


class AmbientOccluder: public Light {
  public:

    AmbientOccluder(void);

    virtual
    ~AmbientOccluder(void);

    virtual bool
    casts_shadows(void);

    void
    set_sampler(Sampler* s_ptr);

    void
    scale_radiance(const float b);

    virtual Vector3D
    get_direction(ShadeRec& sr);

    virtual bool
    in_shadow(const Ray& ray, const ShadeRec& sr);

    virtual RGBColor
    L(ShadeRec& sr);

  private:
    Vector3D u, v, w;
    Sampler* sampler_ptr;
    RGBColor min_amount;
    float ls;
    RGBColor color;
};

inline void
AmbientOccluder::scale_radiance(const float b) {
	ls = b;
}

#endif
