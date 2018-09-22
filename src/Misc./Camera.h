#ifndef __CAMERA__
#define __CAMERA__

#include "../Utilities/Point3D.h"
#include "../SceneObjects/World.h"
#include "../Utilities/Vector3D.h"

class Camera{
  public:
    Camera();

    virtual
    ~Camera();

    Point3D eye;
    Point3D target;
    Vector3D up, u, v, w;

    void
		set_eye(const Point3D& p);
		void
		set_eye(const float x, const float y, const float z);

    void
    set_target(const Point3D& p);
    void
    set_target(const float x, const float y, const float z);

    void
    set_up(const Vector3D& u);
    void
    set_up(const float x, const float y, const float z);

    void
		compute_uvw(void);
};

#endif
