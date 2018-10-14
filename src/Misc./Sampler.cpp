#include <algorithm>
#include "../Utilities/Constants.h"
#include "Sampler.h"

Sampler::Sampler(void)
: 	num_samples(1),
  num_sets(83),
  count(0),
  jump(0) {
samples.reserve(num_samples * num_sets);
setup_shuffled_indices();
}

Sampler::~Sampler(void)
{}

Sampler::Sampler(const int ns)
	: num_samples(ns),
		num_sets(83),
		count(0),
		jump(0) {
	samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}

Sampler::Sampler(const int ns, const int n_sets)
	: num_samples(ns),
		num_sets(n_sets),
		count(0),
		jump(0) {
	samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}

void
Sampler::set_num_sets(const int np) {
	num_sets = np;
}
int
Sampler::get_num_samples(void) {
	return (num_samples);
}

Point2D
Sampler::sample_unit_square(void){
  if(count % num_samples == 0){
    jump = (rand_int() % num_sets);
  }
  return (samples[jump + shuffled_indices[jump+ count++ % num_samples]]);
}

Point3D
Sampler::sample_hemisphere(void) {
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (rand_int() % num_sets) * num_samples;

	return (hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}

void
Sampler::setup_shuffled_indices(void) {
	shuffled_indices.reserve(num_samples * num_sets);
	vector<int> indices;

	for (int x = 0; x < num_samples; x++)
		indices.push_back(x);
	for (int y = 0; y < num_sets; y++) {
		random_shuffle(indices.begin(), indices.end());
		for (int z = 0; z < num_samples; z++)
			shuffled_indices.push_back(indices[z]);
	}
}

void
Sampler::shuffle_samples(void){
random_shuffle(samples.begin(), samples.end());
}


void
Sampler::map_samples_to_unit_disk(void) {
	int size = samples.size();
	float r, phi;		// polar coordinates
	Point2D sp; 		// sample point on unit disk

	disk_samples.reserve(size);

	for (int j = 0; j < size; j++) {
		 // map sample point to [-1, 1] X [-1,1]

		sp.x = 2.0 * samples[j].x - 1.0;
		sp.y = 2.0 * samples[j].y - 1.0;

		if (sp.x > -sp.y) {			// sectors 1 and 2
			if (sp.x > sp.y) {		// sector 1
				r = sp.x;
				phi = sp.y / sp.x;
			}
			else {					// sector 2
				r = sp.y;
				phi = 2 - sp.x / sp.y;
			}
		}
		else {						// sectors 3 and 4
			if (sp.x < sp.y) {		// sector 3
				r = -sp.x;
				phi = 4 + sp.y / sp.x;
			}
			else {					// sector 4
				r = -sp.y;
				if (sp.y != 0.0)	// avoid division by zero at origin
					phi = 6 - sp.x / sp.y;
				else
					phi  = 0.0;
			}
		}

		phi *= PI / 4.0;

		disk_samples[j].x = r * cos(phi);
		disk_samples[j].y = r * sin(phi);
	}

	samples.erase(samples.begin(), samples.end());
}

void
Sampler::map_samples_to_hemisphere(const float exp) {
	int size = samples.size();
	hemisphere_samples.reserve(num_samples * num_sets);

	for (int j = 0; j < size; j++) {
		float cos_phi = cos(2.0 * PI * samples[j].x);
		float sin_phi = sin(2.0 * PI * samples[j].x);
		float cos_theta = pow((1.0 - samples[j].y), 1.0 / (exp + 1.0));
		float sin_theta = sqrt (1.0 - cos_theta * cos_theta);
		float pu = sin_theta * cos_phi;
		float pv = sin_theta * sin_phi;
		float pw = cos_theta;
		hemisphere_samples.push_back(Point3D(pu, pv, pw));
	}
}

void
Sampler::map_samples_to_sphere(void) {
	float r1, r2;
	float x, y, z;
	float r, phi;

	sphere_samples.reserve(num_samples * num_sets);

	for (int j = 0; j < num_samples * num_sets; j++) {
		r1 	= samples[j].x;
    	r2 	= samples[j].y;
    	z 	= 1.0 - 2.0 * r1;
    	r 	= sqrt(1.0 - z * z);
    	phi = TWO_PI * r2;
    	x 	= r * cos(phi);
    	y 	= r * sin(phi);
		sphere_samples.push_back(Point3D(x, y, z));
	}
}
