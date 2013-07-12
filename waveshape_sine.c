#include <stdlib.h>
#include <math.h>

#include "waveshape_sine.h"
#include "config.h"

struct waveshape_s * waveshape_sine_create(unsigned int num_points)
{
	struct waveshape_s *ws = malloc(sizeof(struct waveshape_s));
	ws->size = num_points;
	ws->buffer = malloc(sizeof(float) * num_points);
	ws->preferred_frequency = MIDDLE_C;
	ws->interpolate = 0;

	for(unsigned int i=0; i<num_points; ++i)
	{
		ws->buffer[i] = sin((double)i * 2.0f * 3.14159265358979f / (double)num_points);
	}

	return ws;
}
