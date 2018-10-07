
#include "../Utilities/Constants.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "Pinhole.h"
#include <math.h>
#include "../SceneObjects/World.h"
#include <iostream>

using namespace std;
Pinhole::Pinhole(void)
	:	Camera(),
		d(0),
		zoom(1.0)
{}
Pinhole::~Pinhole(void)
{}

Vector3D
Pinhole::ray_direction(const Point2D& p) const {
	Vector3D a = (p.x * u);
	Vector3D b = (p.y * v);
	Vector3D c = d * w;
	Vector3D dir = p.x * u + p.y * v - d * w;
//	Vector3D dir = Vector3D(p.x * u, p.y * v, -d * w);

//	cout << "u.x: " << u.x << " u.y: " << w.y << " u.z " << u.z << endl;
//	cout << "v.x: " << v.x << " v.y: " << v.y << " v.z " << v.z << endl;
//	cout << "w.x: " << w.x << " w.y: " << w.y << " w.z " << w.z << endl;
//	cout << d << endl;
//	cout << "a.x: " << a.x << " a.y: " << a.y << " a.z " << a.z << endl;
//	cout << "b.x: " << b.x << " b.y: " << b.y << " b.z " << b.z << endl;
//	cout << "c.x: " << c.x << " c.y: " << c.y << " c.z " << c.z << endl;

//	cout << "p.x * u: " << a << " p.y * v: " << b << " d * w" << c << endl;
	//cout << "dir.x: " << dir.x << " dir.y: " << dir.y << " dir.z " << dir.z << endl;

	dir.normalize();
//		cout << "direction set!" << endl;
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
					L += w.tracer_ptr->trace_ray(ray);
				}
//				ray.d.z = ray.d.z;
				cout << "RAY DIRECTION: x " << ray.d.x << " y " << ray.d.y << " z " << ray.d.z << endl;
				cout << "RAY ORIGIN: x" << ray.o.x << " y " << ray.o.y << " z " << ray.o.z << endl;
			L /= vp.num_samples;
			L *= exposure_time;
	//		cout << "Color: " << L.r << L.g << L.b << endl;
	cout << exposure_time << endl;
			w.display_pixel(r, c, L);
		}
		cout << "up.x: " << up.x << " up.y: " << up.y << " up.z " << up.z << endl;
		cout << "all pixels printed" << endl;
		string fileName = "pinhole";
		w.save_image(fileName);
}

/*
void
Pinhole::render_scene(World& w) {
	RGBColor	L;
	ViewPlane	vp = w.vp;
	Ray			ray;
	int 		depth = 0;
//	Point2D 	sp;
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
//							ray.d.z = ;
							L += w.tracer_ptr->trace_ray(ray);
						}

	/*		for (int j = 0; j < vp.num_samples; j++){
					sp = vp.sampler_ptr->sample_unit_square();
					pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
					pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
//					cout << "x " << pp.x << endl;
//					cout << "y " << pp.y << endl;
					ray.d = ray_direction(pp);
//					cout <<  endl;

					cout << "RAY DIRECTION: x " << ray.d.x << " y " << ray.d.y << " z " << ray.d.z << endl;
					cout << "RAY ORIGIN: x" << ray.o.x << " y " << ray.o.y << " z " << ray.o.z << endl;
					L += w.tracer_ptr->trace_ray(ray);
				}

			cout << "RAY DIRECTION: x " << ray.d.x << " y " << ray.d.y << " z " << ray.d.z << endl;
			cout << "RAY ORIGIN: x" << ray.o.x << " y " << ray.o.y << " z " << ray.o.z << endl;
			L /= vp.num_samples;
			//L *= exposure_time;
//			cout << ray.d.x << " x " << ray.d.y << " oy " << ray.d.z << " z " << endl;
//			cout << "ox " << ray.o.x << " oy " << ray.o.y << " oz " << ray.o.z << endl;
			w.display_pixel(r, c, L);
	//		cout << "Color: " << L.r << L.g << L.b << endl;

		}

		cout << "all pixels printed" << endl;


	//save image
		string fileName = "pinhole";
		w.save_image(fileName);

}
*/

void
Pinhole::set_view_distance(float distance) {
	d = distance;
}

void
Pinhole::set_zoom(float zoom_factor) {
	zoom = zoom_factor;
}
