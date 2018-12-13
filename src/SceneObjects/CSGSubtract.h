#ifndef __CSGSUBTRACT__
#define __CSGSUBTRACT__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <vector>

#include "GeometricObject.h"

using namespace std;
//-------------------------------------------------------------------------------- class CSGSubtract

class CSGSubtract: public GeometricObject {
	public:

		CSGSubtract(void);

		virtual CSGSubtract*
		clone(void) const;

		CSGSubtract(const CSGSubtract& c);

		~CSGSubtract (void);

		CSGSubtract&
		operator= (const CSGSubtract& c);

		virtual void
		set_material(Material* material_ptr);

		virtual void
		add_object(GeometricObject* object_ptr);

		int
		get_num_objects(void);

		virtual bool
		hit(const Ray& ray, double& tmin, ShadeRec& s) const;

		virtual bool
		shadow_hit(const Ray& ray, float& tmin);

	protected:

		vector<GeometricObject*> objects;

	private:

		void
		delete_objects(void);

		void
		copy_objects(const vector<GeometricObject*>& rhs_objects);

};


// ------------------------------------------------------------------------------- get_num_objects

inline int
CSGSubtract::get_num_objects(void) {
	return (objects.size());
}

#endif
