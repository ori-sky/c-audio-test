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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "waveshape_sine.h"
#include "config.h"

struct riff_header
{
	unsigned char chunk_id[4];
	unsigned int chunk_size;
	unsigned char format[4];
};

struct fmt_header
{
	unsigned char chunk_id[4];
	unsigned int chunk_size;
	unsigned short format;
	unsigned short num_channels;
	unsigned int sample_rate;
	unsigned int byte_rate;
	unsigned short block_align;
	unsigned short bits_per_sample;
};

struct data_header
{
	unsigned char chunk_id[4];
	unsigned int chunk_size;
};

struct waveshape_s * waveshape_wav_create(FILE * fp)
{
	struct waveshape_s *ws = malloc(sizeof(struct waveshape_s));

	struct riff_header rh;
	struct fmt_header fh;
	struct data_header dh;

	fread(&rh, 1, sizeof(rh), fp);
	fread(&fh, 1, sizeof(fh), fp);
	fread(&dh, 1, sizeof(dh), fp);

	short * buffer = malloc(sizeof(short) * (dh.chunk_size / 2));
	fread(buffer, 1, dh.chunk_size, fp);

	ws->size = dh.chunk_size / 4;
	ws->buffer = malloc(sizeof(float) * ws->size);
	ws->preferred_frequency = (float)fh.sample_rate / (float)ws->size;
	ws->interpolate = 0;

	for(unsigned int i=0; i<ws->size; ++i)
	{
		ws->buffer[i] = (float)buffer[i * 2] * 2 / 32767.0f;
	}

	return ws;
}
