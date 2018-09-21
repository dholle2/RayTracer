#include "Constants.h"

#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"

#include "Ray.h"
#include "World.h"

void
World::build(void){
  vp.set_hres(200);
  vp.set_vres(200);
  vp.set_s(1.0);
  vp.set_gamma(1.0);

  background_color = black;

}
