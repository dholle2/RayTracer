
#ifndef __AREA_LIGHT__

//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.






#include "../Utilities/Material.h"
#include "../SceneObjects/GeometricObject.h"

class AreaLight: public Light {


      AreaLight(void);

      AreaLight(const AreaLight& al);

      virtual AreaLight*
      clone(void);

      virtual
      ~AreaLight(void);

      AreaLight&
      operator= (const AreaLight& rhs);

      void
      set_object(GeometricObject* obj_ptr);

      virtual Vector3D
      get_direction(ShadeRec& s);

      virtual RGBColor
      L(ShadeRec& sr);

      virtual bool
      in_shadow(const Ray& ray, const ShadeRec& sr);

      virtual float
      G(const ShadeRec& sr) const;

      virtual float
      pdf(const ShadeRec& sr) const;

      virtual bool
      casts_shadows(void);

      private:

        GeometricObject* 	object_ptr;
        Material* 			material_ptr;	 // will be an emissive material
        Point3D				sample_point;

        Normal				light_normal;    // assigned in get_direction - which therefore can't be const for any light
        Vector3D			wi;			     // unit direction from hit point being shaded to sample point on light surface
      };



      inline void
      AreaLight::set_object(GeometricObject* obj_ptr) {
        object_ptr = obj_ptr;
        material_ptr = object_ptr->get_material();
      }


