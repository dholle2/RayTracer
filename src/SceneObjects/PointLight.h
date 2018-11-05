
#ifndef __POINT_LIGHT__
#define __POINT_LIGHT__
// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "../Utilities/RGBColor.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "Light.h"
#include "../Utilities/Material.h"
#include "GeometricObject.h"
class PointLight: public Light {
public:

      PointLight(void);

      PointLight(float x, float y, float z);

      virtual PointLight*
      clone(void);

      virtual
      ~PointLight(void);

      PointLight&
      operator= (const PointLight& rhs);

//      void
//      set_object(GeometricObject* obj_ptr);

      virtual Vector3D
      get_direction(ShadeRec& s);

      virtual RGBColor
      L(ShadeRec& sr);

      virtual bool
      in_shadow(const Ray& ray, const ShadeRec& sr);

      virtual void
      scale_radiance(float b);
/*
      virtual float
      G(const ShadeRec& sr) const;
*/
      virtual bool
      casts_shadows(void);


/*
      virtual float
      pdf(const ShadeRec& sr) const;
*/
      private:
        float ls;
        Point3D location;
        RGBColor color;
        GeometricObject* 	object_ptr;
        Material* 			material_ptr;	 // will be an emissive material
        Point3D				sample_point;
        Normal				light_normal;    // assigned in get_direction - which therefore can't be const for any light
        Vector3D			wi;			     // unit direction from hit point being shaded to sample point on light surface
};// --------------------------------------------------------------- set_object
  /*    inline
      void
      PointLight::set_object(GeometricObject* obj_ptr) {
        	object_ptr = obj_ptr;	material_ptr = object_ptr->get_material();
      }
*/
      #endif
