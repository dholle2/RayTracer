#ifndef __PINHOLE__
#define __PINHOLE__

#include "../Utilities/Point2D.h"
#include "Camera.h"
#include <string>

using namespace std;

class Pinhole: public Camera {
	public:

		Pinhole();
		virtual
		~Pinhole();

    void
		set_view_distance(const float vpd);

    Vector3D
		ray_direction(const Point2D& p) const;

		virtual void
		render_scene(World& w, string picName);

    void
    set_zoom(float zoom_factor);

      float d;
      float zoom;

};

#endif
