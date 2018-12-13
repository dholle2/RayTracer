#include "src/SceneObjects/World.h"
#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
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

/*
time_t before;
time(&before);
World* w6 = new World();
for(int x = 67; x < 100; x++){
  World* w6 = new World();
  w6->buildAnimationFrames(x);

  string imgName = "Animation";
  std::stringstream sstm;
  sstm << imgName << x;
  string result = sstm.str();

  w6->camera_ptr->render_scene(*w6, result);
  delete w6;

}

time_t after;
time(&after);
cout << "Image finished, sir!" << endl;
cout << "seconds: " << difftime(after, before) << endl;
*/
/*
int randNum;
for(int x = 0; x < 100; x++){
  randNum = rand()%(1-(-1) + 1) + (-1);
  cout << randNum << endl;
}
*/
/*
double x1, y1, z1, x2, y2, z2;
x1 = 0;
y1 = 0;
z1 = 0;

x2 = 5;
y2 = 5;
z2 = 5;
double x, y, z;
x = x1-x2;
y = y1-y2;
z = z1-z2;
x*=x;
y*=y;
z*=z;
double result = x+y+z;
result = sqrt(result);
cout << "Result: " << result << endl;
*/

time_t before;
time(&before);
World* w6 = new World();
w6->buildCSG();
w6->camera_ptr->render_scene(*w6, "CSGSubtract");
time_t after;
time(&after);
cout << "Image finished, sir!" << endl;
cout << "seconds: " << difftime(after, before) << endl;


return 0;

}
