#ifndef __VIEWPLANE__
#define __VIEWPLANE__

class ViewPlane{
  public:
    int hres;
    int vres;
    float s; //size
    float gamma;
    float inv_gamma;

    void set_hres(int h);
    void set_vres(int v);
    void set_s(float size);
    void set_gamma(float g);

    ViewPlane(void);
};

#endif
