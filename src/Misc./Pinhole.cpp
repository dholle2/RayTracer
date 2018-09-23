
#include "../Utilities/Constants.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "Pinhole.h"
#include <math.h>
#include "../SceneObjects/World.h"

Pinhole::Pinhole(void)
	:	Camera(),
		d(500),
		zoom(1.0)
{}
Pinhole::~Pinhole(void)
{}

Vector3D
Pinhole::ray_direction(const Point2D& p) const {
	Vector3D dir = p.x * u + p.y * v - d * w;
	dir.normalize();
	return(dir);
}

void
Pinhole::render_scene(World& w) {
	RGBColor	L;
	ViewPlane	vp(w.vp);
	Ray			ray;
	int 		depth = 0;
	Point2D 	pp;		// sample point on a pixel
	int n = (int)sqrt((float)vp.num_samples);

	vp.s /= zoom;
	ray.o = eye;

	for (int r = 0; r < vp.vres; r++)			// up
		for (int c = 0; c < vp.hres; c++) {		// across
			L = black;

			for (int p = 0; p < n; p++)			// up pixel
				for (int q = 0; q < n; q++) {	// across pixel
					pp.x = vp.s * (c - 0.5 * vp.hres + (q + 0.5) / n);
					pp.y = vp.s * (r - 0.5 * vp.vres + (p + 0.5) / n);
					ray.d = ray_direction(pp);
					L += w.tracer_ptr->trace_ray(ray, depth);
				}

			L /= vp.num_samples;
			L *= exposure_time;
			w.display_pixel(r, c, L);
		}

}

void
Pinhole::set_view_distance(float _d) {
	d = _d;
}

void
Pinhole::set_zoom(float zoom_factor) {
	zoom = zoom_factor;
}
