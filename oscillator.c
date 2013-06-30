/*
 * Copyright (c) 2013, David Farrell <shokku.ra@gmail.com>
 *  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * 
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

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
	float increment = osc->frequency * osc->waveshape->size / SAMPLE_RATE;
	increment *= osc->speed;

	for(unsigned int i=0; i<frames; ++i)
	{
		float x1 = (int)osc->position;
		float x2 = ceil(osc->position);

		float y1 = osc->waveshape->buffer[(int)x1];
		float y2 = osc->waveshape->buffer[(int)x2];

		buffer[i * 2 + 0] = y1;
		buffer[i * 2 + 1] = y1;

		osc->position += increment;

		if(osc->position >= osc->waveshape->size) osc->position -= osc->waveshape->size;
		else if(osc->position < 0) osc->position += osc->waveshape->size;
	}

	return 0;
}
