#ifndef __CAMERA__
#define __CAMERA__

#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"

class World;

class Camera{
  public:
    Camera();

    virtual
    ~Camera();

    Point3D eye;
    Point3D lookat;
    Vector3D up, u, v, w;
    float exposure_time;


    virtual void
		render_scene(World& w) =0;
    void
		set_eye(const Point3D& p);
		void
		set_eye(const float x, const float y, const float z);

    void
    set_lookat(const Point3D& p);
    void
    set_exposure_time(float length);

    void
    set_lookat(const float x, const float y, const float z);

    void
    set_up(const Vector3D& u);
    void
    set_up(const float x, const float y, const float z);

    void
		compute_uvw(void);
};

#endif
