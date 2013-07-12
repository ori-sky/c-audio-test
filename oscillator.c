#include <stdlib.h>
#include <math.h>

#include "oscillator.h"
#include "config.h"

struct oscillator_s *oscillator_create(struct waveshape_s *waveshape)
{
	struct oscillator_s *osc = malloc(sizeof(struct oscillator_s));
	osc->waveshape = waveshape;
	osc->frequency = waveshape->preferred_frequency;
	osc->speed = 1;
	osc->position = 0;
	return osc;
}

int oscillator_cb(float *buffer, unsigned long frames, struct oscillator_s *osc)
{
	double increment = osc->frequency * osc->waveshape->size / SAMPLE_RATE;
	increment *= osc->speed;

	for(unsigned int i=0; i<frames; ++i)
	{
		double x1 = (int)osc->position;
		double x2 = ceil(osc->position);

		double y1 = osc->waveshape->buffer[(int)x1];
		double y2 = osc->waveshape->buffer[(int)x2];

		buffer[i * 2 + 0] = y1;
		buffer[i * 2 + 1] = y1;

		osc->position += increment;

		for(; osc->position >= osc->waveshape->size;) osc->position -= osc->waveshape->size;
		for(; osc->position < 0;) osc->position += osc->waveshape->size;
	}

	return 0;
}
