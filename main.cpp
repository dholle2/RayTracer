#include "src/SceneObjects/World.h"
#include <iostream>

//using namespace std;
int
main(void){
  World w;
  std::cout << "world viewplane hres, vres = " << w.vp.hres << ", " << w.vp.vres << std::endl;
  w.build();
  cout << "it is built!" << endl;
  w.render_scene_ortho();
//  delete w;

  World w2;
  w2.build();
  w2.render_scene_perspective();
//  delete w2;

  World w3;
  w3.build();
  w3.render_scene_jittering();

  World w4;
  w4.build();
  w4.camera_ptr->render_scene(w4);

  return 0;

}
