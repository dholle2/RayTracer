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
#include "GlossySpecular.h"

class Phong: public Material {
  public:

      Phong(void);

      virtual Phong*
      clone(void) const;

      virtual RGBColor
      shade(ShadeRec& s);

      virtual RGBColor
      area_light_shade(ShadeRec& s);

      Lambertian* ambient_brdf;
      Lambertian* diffuse_brdf;
      GlossySpecular* specular_brdf;

//ambient/diffuse
      void
  		set_ka(const float k);

  		void
  		set_kd(const float k);

  		void
  		set_cd(const RGBColor c);

  		void
  		set_cd(const float r, const float g, const float b);

  		void
  		set_cd(const float c);

//glossy
      void
      set_ks(const float ks);

      void
      set_exp(const float exp);

      void
      set_cs(const RGBColor& c);

      void
      set_cs(const float r, const float g, const float b);

      void
      set_cs(const float c);
};

inline void
Phong::set_ks(const float k) {
	specular_brdf->set_ks(k);
}

// -------------------------------------------------------------- set_exp

inline void
Phong::set_exp(const float e) {
	specular_brdf->set_exp(e);
}


// -------------------------------------------------------------- set_cs

inline void
Phong::set_cs(const RGBColor& c) {
	specular_brdf->set_cs(c);
}


// ---------------------------------------------------------------- set_cs

inline void
Phong::set_cs(const float r, const float g, const float b) {
	specular_brdf->set_cs(r, g, b);
}


// ---------------------------------------------------------------- set_cs

inline void
Phong::set_cs(const float c) {
	specular_brdf->set_cs(c);
}


inline void
Phong::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void
Phong::set_kd (const float kd) {
	diffuse_brdf->set_kd(kd);
}


// ---------------------------------------------------------------- set_cd

inline void
Phong::set_cd(const RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}


// ---------------------------------------------------------------- set_cd

inline void
Phong::set_cd(const float r, const float g, const float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

// ---------------------------------------------------------------- set_cd

inline void
Phong::set_cd(const float c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

#endif
