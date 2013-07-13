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

float oscillator_cb(struct oscillator_s *osc)
{
	double increment = osc->frequency * osc->waveshape->size / SAMPLE_RATE;
	increment *= osc->speed;

	double x1 = (int)osc->position;
	double x2 = ceil(osc->position);

	double y1 = osc->waveshape->buffer[(int)x1];
	double y2 = osc->waveshape->buffer[(int)x2];

	osc->position += increment;

	for(; osc->position >= osc->waveshape->size;) osc->position -= osc->waveshape->size;
	for(; osc->position < 0;) osc->position += osc->waveshape->size;

	return y1;
}
