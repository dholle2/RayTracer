#include "Phong.h"

Phong::Phong (void)
{
  ambient_brdf = new Lambertian();
  diffuse_brdf = new Lambertian();
  specular_brdf = new PerfectSpecular();
}


  RGBColor
  Phong::shade(ShadeRec& sr){
    Vector3D wo = -sr.ray.d;
//    RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr); //no ambient pointer, find out how to use directional instead
  RGBColor L = black;
    int num_lights = sr.w.lights.size();

    for(int j = 0; j < num_lights; j++){
      Vector3D wi = sr.w.lights[j]->get_direction(sr);
      float ndotwi = sr.normal * wi;

      if(ndotwi > 0.0){
        L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi)) * sr.w.lights[j]->L(sr) * ndotwi;
      }
    }

    return (L);
  }
