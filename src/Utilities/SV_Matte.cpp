#include "SV_Matte.h"
#include <iostream>

using namespace std;

SV_Matte::SV_Matte (void)
{
  ambient_brdf = new SV_Lambertian();
//  ambient_brdf->set_kd(1.0);
//  ambient_brdf->set_cd(1,1,1);

  diffuse_brdf = new SV_Lambertian();
//  diffuse_brdf->set_kd(1.0);
//  diffuse_brdf->set_cd(1,1,1);
}


SV_Matte*
SV_Matte::clone(void) const {
	return (new SV_Matte(*this));
}


RGBColor
SV_Matte::shade(ShadeRec& sr){
  Vector3D wo = -sr.ray.d;
//  cout << "ABOUT TO DO RHO" << endl;
  RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr); //no ambient pointer, find out how to use directional instead
//  RGBColor L = black;
//  cout << "SV_Matte Color from Ambient: " << L.r << L.g << L.b << endl;
  int num_lights = sr.w.lights.size();

  for(int j = 0; j < num_lights; j++){
    Light* light_ptr = sr.w.lights[j];
    Vector3D wi = light_ptr->get_direction(sr);
    wi.normalize();
    float ndotwi = sr.normal * wi;
    float ndotwo = sr.normal * wo;

    if(ndotwi > 0.0 & ndotwo > 0.0){
      bool in_shadow = false;
          //shadow test
      if(sr.w.lights[j]->casts_shadows()){
        Ray shadowRay(sr.hit_point, wi);
        in_shadow = light_ptr->in_shadow(shadowRay, sr);
      }
      if(!in_shadow){
        L += diffuse_brdf->f(sr, wo, wi) * light_ptr->L(sr) * light_ptr->G(sr) * ndotwi; /*/ sr.w.lights[j]->pdf(sr)*/;
      }else{
//        cout << "in shadow" << endl;
      }
//      cout << "sr.w.lights[j]->G(sr) " << sr.w.lights[j]->G(sr) << endl;
//      cout << "sr.w.lights[j]->pdf(sr) " << sr.w.lights[j]->pdf(sr) << endl;
    }
  }//end for
  return (L);
}



RGBColor
SV_Matte::area_light_shade(ShadeRec& sr){
//  cout << "hi" << endl;
  Vector3D wo = -sr.ray.d;
  RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr); //no ambient pointer, find out how to use directional instead
//  RGBColor L = black;
//  cout << "SV_Matte Color from Ambient: " << L.r << L.g << L.b << endl;
  int num_lights = sr.w.lights.size();

  for(int j = 0; j < num_lights; j++){
    Vector3D wi = sr.w.lights[j]->get_direction(sr);
    float ndotwi = sr.normal * wi;
    float ndotwo = sr.normal * wo;


    if(ndotwi > 0.0 & ndotwo > 0.0){
      bool in_shadow = false;
          //shadow test
      if(sr.w.lights[j]->casts_shadows()){
        Ray shadowRay(sr.hit_point, wi);
        in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
      }
      if(!in_shadow){
        L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * sr.w.lights[j]->G(sr) * ndotwi / sr.w.lights[j]->pdf(sr);
      }else{
//        cout << "in shadow" << endl;
      }
  //    cout << "sr.w.lights[j]->G(sr) " << sr.w.lights[j]->G(sr) << endl;
  //    cout << "sr.w.lights[j]->pdf(sr) " << sr.w.lights[j]->pdf(sr) << endl;
    }
  }//end for
  return (L);
}
