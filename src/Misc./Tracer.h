#ifndef __TRACER__
#define __TRACER__

#include "../Utilities/Constants.h"
#include "../Utilities/Ray.h"
#include "../Utilities/RGBColor.h"
//#include "../Utilities/ShadeRec.h"
//#include "../SceneObjects/World.h"

class World;

class Tracer {
	public:

		Tracer(void);

		Tracer(World* world_ptr);

    virtual RGBColor
    trace_ray(const Ray& ray) const;

		virtual RGBColor
		trace_ray(const Ray ray, const int depth);
/*		virtual RGBColor			// RayCast
		trace_ray(const Ray ray, float& tmin, const int depth);
*/
		virtual void
		kill(void);

    virtual
    ~Tracer(void);
  protected:
    World* world_ptr;
};

#endif
