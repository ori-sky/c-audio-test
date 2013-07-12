#include <stdlib.h>
#include <math.h>

#include "waveshape_test.h"
#include "config.h"

struct waveshape_s * waveshape_test_create(void)
{
	struct waveshape_s *ws = malloc(sizeof(struct waveshape_s));
	ws->size = SAMPLE_RATE * 2;
	ws->buffer = malloc(sizeof(float) * ws->size);
	ws->preferred_frequency = 1;
	ws->interpolate = 0;

	for(unsigned int i=0; i<SAMPLE_RATE; ++i)
	{
		ws->buffer[i] = sin((double)i * 2.0f * 3.14159265358979f * ws->size);
		ws->buffer[SAMPLE_RATE + i] = sin((double)i * 3.0f * 3.14159265358979f * ws->size);
	}

	return ws;
}
