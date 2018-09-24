#include "Camera.h"

Camera::Camera(void)
	:	eye(0, 0, 500),
		lookat(0),
		up(0, 1, 0),
		u(1, 0, 0),
		v(0, 1, 0),
		w(0, 0, 1)
{}

Camera::~Camera(void)
{}

void
Camera::compute_uvw(void){
  w = eye - lookat;
  w.normalize();
  u = up ^ w;
  u.normalize();
  v = w ^ u;

	if (eye.x == lookat.x && eye.z == lookat.z && eye.y > lookat.y) { // camera looking vertically down
		u = Vector3D(0, 0, 1);
		v = Vector3D(1, 0, 0);
		w = Vector3D(0, 1, 0);
	}

	if (eye.x == lookat.x && eye.z == lookat.z && eye.y < lookat.y) { // camera looking vertically up
		u = Vector3D(1, 0, 0);
		v = Vector3D(0, 0, 1);
		w = Vector3D(0, -1, 0);
	}

}

//setters

  void
  Camera::set_eye(const Point3D& x){
    eye = x;
  }
  void
  Camera::set_eye(const float x, const float y, const float z){
    eye.x = x;
    eye.y = y;
    eye.z = z;
  }

  void
  Camera::set_lookat(const Point3D& x){
    lookat = x;
  }
  void
  Camera::set_lookat(const float x, const float y, const float z){
    lookat.x = x;
    lookat.y = y;
    lookat.z = z;
  }

  void
  Camera::set_up(const Vector3D& x){
    up = x;
  }
  void
  Camera::set_up(const float x, const float y, const float z){
    up.x = x;
    up.y = y;
    up.z = z;
  }
