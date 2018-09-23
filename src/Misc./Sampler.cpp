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
  return (samples[count++ % (num_samples * num_sets)]);
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
