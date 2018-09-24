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

cout << "did ortho, sir!" << endl;

  World w2;
  w2.build();
  w2.render_scene_perspective();
//  delete w2;
cout << "did perspective, sir!" << endl;

  World w3;
  w3.build();
  w3.render_scene_multijittered();
  cout << "did multijittered sampling, sir!" << endl;


  World w4;
  w4.build();
  w4.camera_ptr->render_scene(w4);
  cout << "did camera, sir!" << endl;

  return 0;

}
