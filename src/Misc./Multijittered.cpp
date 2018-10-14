#include "Multijittered.h"


Multijittered::Multijittered(void)
	: Sampler()
{}

Multijittered::Multijittered(int num_samples)
	: 	Sampler(num_samples) {
	generate_samples();
}

Multijittered::Multijittered(int num_samples, int m)
	: 	Sampler(num_samples, m) {
	generate_samples();
}
Multijittered::~Multijittered(void)
{}

Multijittered*
Multijittered::clone(void) const {
	return (new Multijittered(*this));
}


void
Multijittered::generate_samples(void) {
// num_samples needs to be a perfect square

int n = (int)sqrt((float)num_samples);
float subcell_width = 1.0 / ((float) num_samples);

// fill the samples array with dummy points to allow us to use the [ ] notation when we set the
// initial patterns

Point2D fill_point;
for (int j = 0; j < num_samples * num_sets; j++)
	samples.push_back(fill_point);

// distribute points in the initial patterns

for (int p = 0; p < num_sets; p++)
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			samples[i * n + j + p * num_samples].x = (i * n + j) * subcell_width + rand_float(0, subcell_width);
			samples[i * n + j + p * num_samples].y = (j * n + i) * subcell_width + rand_float(0, subcell_width);
		}

// shuffle x coordinates

for (int p = 0; p < num_sets; p++)
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			int k = rand_int(j, n - 1);
			float t = samples[i * n + j + p * num_samples].x;
			samples[i * n + j + p * num_samples].x = samples[i * n + k + p * num_samples].x;
			samples[i * n + k + p * num_samples].x = t;
		}

// shuffle y coordinates

for (int p = 0; p < num_sets; p++)
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			int k = rand_int(j, n - 1);
			float t = samples[j * n + i + p * num_samples].y;
			samples[j * n + i + p * num_samples].y = samples[k * n + i + p * num_samples].y;
			samples[k * n + i + p * num_samples].y = t;
	}
}
