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
    RGBColor L = ambient_brdf->rho(sr, wo); //* sr.w.ambient_ptr->L(sr); //no ambient pointer, find out how to use directional instead
//  RGBColor L = black;
//  cout << "Phong Color from Ambient: " << L.r << L.g << L.b << endl;
    int num_lights = sr.w.lights.size();

    for(int j = 0; j < num_lights; j++){
      Vector3D wi = sr.w.lights[j]->get_direction(sr);
      float ndotwi = sr.normal * wi;



      if(ndotwi > 0.0){
        L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi)) * sr.w.lights[j]->L(sr) * ndotwi;
  //      cout << "Phong Color from specular: " << specular_brdf->f(sr, wo, wi).r << specular_brdf->f(sr, wo, wi).g << specular_brdf->f(sr, wo, wi).b << endl;
      }
    }
    return (L);
  }
