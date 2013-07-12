#ifndef WAVESHAPE_H
#define WAVESHAPE_H

struct waveshape_s
{
	unsigned int size;
	float *buffer;
	double preferred_frequency;
	unsigned char interpolate;
};

#endif
