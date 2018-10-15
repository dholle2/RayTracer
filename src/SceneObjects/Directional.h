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

  void
  set_ls(float l);

  virtual Vector3D
  get_direction(ShadeRec& sr);

  virtual RGBColor
  L(ShadeRec& sr);

  bool
  in_shadow(const Ray& ray, const ShadeRec& sr);

  virtual bool
  casts_shadows(void);

  float		ls;
  RGBColor	color;
  Vector3D	dir;

};

#endif
