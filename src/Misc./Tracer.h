#ifndef __TRACER__
#define __TRACER__

#include "../Utilities/Constants.h"
#include "../Utilities/Ray.h"
#include "../Utilities/RGBColor.h"

class World;

class Tracer {
	public:

		Tracer(void);

		Tracer(World* world_ptr);

    virtual RGBColor
    trace_ray(const Ray& ray) const;

    virtual
    ~Tracer(void);
  protected:
    World* world_ptr;
};

#endif
