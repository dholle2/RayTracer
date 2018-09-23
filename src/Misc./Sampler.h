#ifndef __SAMPLER__
#define __SAMPLER__

#include <vector>
#include <math.h>

#include "../Utilities/Point2D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Maths.h"

using namespace std;
class Sampler {
	public:

		Sampler(void);
		Sampler(const int num);
		Sampler(const int num, const int sets);
    virtual
		~Sampler(void);

    void
		set_num_sets(int num);
    int
    get_num_samples(void);

    void
		setup_shuffled_indices(void);
		virtual void
		generate_samples(void) = 0;
    Point2D
    sample_unit_square(void);
    void
    shuffle_samples(void);

    int 		num_samples;
		int 		num_sets;
		vector<Point2D>			samples;
		vector<int>				shuffled_indices;
    unsigned long 	count;
		int 		jump;
};
#endif
