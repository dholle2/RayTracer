#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "Light.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/RGBColor.h"
#include "World.h"
#include "../Utilities/ShadeRec.h"

class Directional: public Light {
  public:

  Directional(void);

  virtual
  ~Directional(void);

  void
  set_direction(Vector3D d);

  void
  set_direction(float x, float y, float z);

  virtual Vector3D
  get_direction(void);

  virtual RGBColor
  L(ShadeRec& sr);

  float		ls;
  RGBColor	color;
  Vector3D	dir;

};

#endif
