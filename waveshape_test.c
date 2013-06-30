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
