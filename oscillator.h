#include "waveshape.h"

#ifndef OSCILLATOR_H
#define OSCILLATOR_H

struct oscillator_s
{
	struct waveshape_s *waveshape;
	double frequency;
	double speed;
	double position;
};

extern struct oscillator_s * oscillator_create(struct waveshape_s *waveshape);
extern int oscillator_cb(float *buffer, unsigned long frames, struct oscillator_s *osc);

#endif
