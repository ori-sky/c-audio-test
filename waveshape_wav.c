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

struct waveshape_s * waveshape_wav_create(FILE *fp)
{
	struct waveshape_s *ws = malloc(sizeof(struct waveshape_s));

	struct riff_header rh;
	struct fmt_header fh;
	struct data_header dh;

	fread(&rh, 1, sizeof(rh), fp);
	fread(&fh, 1, sizeof(fh), fp);
	fread(&dh, 1, sizeof(dh), fp);

	short *buffer = malloc(sizeof(short) * (dh.chunk_size / 2));
	fread(buffer, 1, dh.chunk_size, fp);

	ws->size = dh.chunk_size / 4;
	ws->buffer = malloc(sizeof(float) * ws->size);
	ws->preferred_frequency = (double)fh.sample_rate / (double)ws->size;
	ws->interpolate = 0;

	for(unsigned int i=0; i<ws->size; ++i)
	{
		ws->buffer[i] = (double)buffer[i * 2] * 2 / 32767.0f;
	}

	return ws;
}
