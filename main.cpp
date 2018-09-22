#include "src/SceneObjects/World.h"
#include <iostream>

//using namespace std;
int
main(void){
  World w;
  std::cout << "world viewplane hres, vres = " << w.vp.hres << ", " << w.vp.vres << std::endl;
  w.build();
  cout << "it is built!" << endl;
  w.render_scene();

  return 0;

}
