#ifndef __MULTI_JITTERED__
#define __MULTI_JITTERED__

#include "Sampler.h"

class Multijittered: public Sampler{

  public:
    Multijittered(void);
    Multijittered(int num_samples);
		Multijittered(int num_samples, int m);

    virtual
		~Multijittered(void);
    virtual void
    generate_samples(void);
};
#endif
