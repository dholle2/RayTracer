#ifndef __PHONG__
#define __PHONG__

#include <math.h>
#include "../Utilities/Constants.h"
#include "../Utilities/BBox.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"
#include "Material.h"
#include "Lambertian.h"
#include "PerfectSpecular.h"

class Phong: public Material {
  public:

      Phong(void);

      virtual RGBColor
      shade(ShadeRec& s);

      Lambertian* ambient_brdf;
      Lambertian* diffuse_brdf;
      PerfectSpecular* specular_brdf;

};

#endif
