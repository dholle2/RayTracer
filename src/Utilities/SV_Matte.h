#ifndef __SV_MATTE__
#define __SV_MATTE__

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
#include "SV_Lambertian.h"
#include "GlossySpecular.h"

class SV_Matte: public Material {
public:
      SV_Matte(void);

      virtual SV_Matte*
      clone(void) const;

      virtual RGBColor
      shade(ShadeRec& s);

      virtual RGBColor
      area_light_shade(ShadeRec& s);

      void
      set_cd(Texture* t_ptr);

      void
      set_kd(float k);

private:

      SV_Lambertian* ambient_brdf;
      SV_Lambertian* diffuse_brdf;

};

inline void
SV_Matte::set_cd(Texture* t_ptr) {
	ambient_brdf->set_cd(t_ptr);
  diffuse_brdf->set_cd(t_ptr);

}

inline void
SV_Matte::set_kd(float k) {
	ambient_brdf->set_kd(k);
  diffuse_brdf->set_kd(k);

}

#endif
