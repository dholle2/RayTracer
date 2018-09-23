#include "ViewPlane.h"
#include <iostream>

using namespace std;
ViewPlane::ViewPlane(void)
{
  hres = 10;
  vres = 10;
  s = 1;
  gamma = 1;
  inv_gamma = 1;
//  num_samples = 10;
}

void
ViewPlane::set_hres(int h){
  hres = h;
}

void
ViewPlane::set_vres(int v){
  vres = v;
}

void
ViewPlane::set_s(float size){
  s = size;
}

void
ViewPlane::set_gamma(float g){
  gamma = g;
  inv_gamma = (1/g);
}

void
ViewPlane::set_sampler(Sampler* sp){
  cout << "Setting Sampler!" << endl;
  if(sampler_ptr != NULL){
    cout << "about to delete sampler_ptr!" << endl;
    //delete sampler_ptr;
    cout << "sampler_ptr deleted!" << endl;
    sampler_ptr = NULL;
  }
  num_samples = sp->get_num_samples();
  cout << "num_samples: " << num_samples << endl;
  sampler_ptr = sp;
}

void
ViewPlane::set_samples(const int n){
  num_samples = n;

  if(sampler_ptr){
    delete sampler_ptr;
    sampler_ptr = NULL;
  }
  if(num_samples > 1){
    sampler_ptr = new Multijittered(num_samples);
  }else{
    sampler_ptr = NULL;//= new Regular(1);
    cout << "should set to regular sampler, but thats not made yet!" << endl;
  }
}
