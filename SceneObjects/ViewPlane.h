#ifndef __VIEWPLANE__
#define __VIEWPLANE__

class ViewPlane{
  public:
    int hres;
    int vres;
    float s; //size
    float gamma;
    float inv_gamma;

    set_hres(int h);
    set_vres(int v);
    set_s(float size);
    set_gamma(float g);
}
