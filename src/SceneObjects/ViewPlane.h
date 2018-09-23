#ifndef __VIEWPLANE__
#define __VIEWPLANE__
#include "../Misc./Sampler.h"
#include "../Misc./Multijittered.h"

class ViewPlane{
  public:
    int hres;
    int vres;
    float s; //size
    float gamma;
    float inv_gamma;
    int num_samples;
    Sampler* sampler_ptr;

    void set_hres(int h);
    void set_vres(int v);
    void set_s(float size);
    void set_gamma(float g);
    void set_sampler(Sampler* sp);
    void set_samples(const int n);
    ViewPlane(void);
};

#endif
