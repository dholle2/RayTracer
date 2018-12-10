#include "src/SceneObjects/World.h"
#include <iostream>
#include <string>
#include <time.h>
//using namespace std;
int
main(void){
/*
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
*/
/*
  World w4;
  w4.buildReflective();
  w4.camera_ptr->render_scene(w4, "Reflective");
  cout << "did camera, sir!" << endl;
*/
/*
  World w5;
  w5.buildMesh();
  time_t before;
  time(&before);
  w5.camera_ptr->render_scene(w5, "Mesh");
  time_t after;
  time(&after);
  cout << "did camera, sir!" << endl;
  cout << "seconds: " << difftime(after, before) << endl;
*/
/*
World w5;
w5.buildAreaLight();
time_t before;
time(&before);
w5.camera_ptr->render_scene(w5, "Area Light");
time_t after;
time(&after);
cout << "did camera, sir!" << endl;
cout << "seconds: " << difftime(after, before) << endl;
*/

World w6;
w6.buildProceduralTexture();
time_t before;
time(&before);
w6.camera_ptr->render_scene(w6, "Procedural Texture");
time_t after;
time(&after);
cout << "did camera, sir!" << endl;
cout << "seconds: " << difftime(after, before) << endl;

return 0;

}
