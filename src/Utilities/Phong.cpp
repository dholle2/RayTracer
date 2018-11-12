#include "Phong.h"
#include <iostream>

using namespace std;

Phong::Phong (void)
{
  ambient_brdf = new Lambertian();
//  ambient_brdf->set_kd(1.0);
//  ambient_brdf->set_cd(1,1,1);

  diffuse_brdf = new Lambertian();
//  diffuse_brdf->set_kd(1.0);
//  diffuse_brdf->set_cd(1,1,1);

  specular_brdf = new GlossySpecular();
}


Phong*
Phong::clone(void) const {
	return (new Phong(*this));
}


RGBColor
Phong::shade(ShadeRec& sr){
  Vector3D wo = -sr.ray.d;
  RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr); //no ambient pointer, find out how to use directional instead
//  RGBColor L = black;
//  cout << "Phong Color from Ambient: " << L.r << L.g << L.b << endl;
  int num_lights = sr.w.lights.size();

  for(int j = 0; j < num_lights; j++){
    Vector3D wi = sr.w.lights[j]->get_direction(sr);
    float ndotwi = sr.normal * wi;



    if(ndotwi > 0.0){
      bool in_shadow = false;
          //shadow test
      if(sr.w.lights[j]->casts_shadows()){
        Ray shadowRay(sr.hit_point, wi);
        in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
      }
      if(!in_shadow){
        L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi)) * sr.w.lights[j]->L(sr) /** sr.w.lights[j]->G(sr) */* ndotwi; /*/ sr.w.lights[j]->pdf(sr)*/;
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
Phong::area_light_shade(ShadeRec& sr){
//  cout << "hi" << endl;
  Vector3D wo = -sr.ray.d;
  RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr); //no ambient pointer, find out how to use directional instead
//  RGBColor L = black;
//  cout << "Phong Color from Ambient: " << L.r << L.g << L.b << endl;
  int num_lights = sr.w.lights.size();

  for(int j = 0; j < num_lights; j++){
    Vector3D wi = sr.w.lights[j]->get_direction(sr);
    float ndotwi = sr.normal * wi;



    if(ndotwi > 0.0){
      bool in_shadow = false;
          //shadow test
      if(sr.w.lights[j]->casts_shadows()){
        Ray shadowRay(sr.hit_point, wi);
        in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
      }
      if(!in_shadow){
        L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi)) * sr.w.lights[j]->L(sr) * sr.w.lights[j]->G(sr) * ndotwi / sr.w.lights[j]->pdf(sr);
      }else{
//        cout << "in shadow" << endl;
      }
  //    cout << "sr.w.lights[j]->G(sr) " << sr.w.lights[j]->G(sr) << endl;
  //    cout << "sr.w.lights[j]->pdf(sr) " << sr.w.lights[j]->pdf(sr) << endl;
    }
  }//end for
  return (L);
}
