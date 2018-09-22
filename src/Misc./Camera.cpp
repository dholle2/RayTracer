#include "Camera.h"

Camera::Camera(void)
	:	eye(0, 0, 500),
		target(0),
		up(0, 1, 0),
		u(1, 0, 0),
		v(0, 1, 0),
		w(0, 0, 1)
{}

Camera::~Camera(void)
{}

void
Camera::compute_uvw(void){
  w = eye - target;
  w.normalize();
  u = up ^ w;
  u.normalize();
  v = w ^ u;
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
  Camera::set_target(const Point3D& x){
    target = x;
  }
  void
  Camera::set_target(const float x, const float y, const float z){
    target.x = x;
    target.y = y;
    target.z = z;
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