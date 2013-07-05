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
#include <string.h>
#include <math.h>

#include "portaudio.h"
#include "config.h"
#include "oscillator.h"
#include "waveshape_sine.h"
#include "waveshape_wav.h"
#include "waveshape_test.h"

static struct oscillator_s *osc1 = NULL;

static unsigned char assert_pa_error(PaError err, const char *msg)
{
	fprintf(stderr, "%s [%s]\n", msg, (err == paNoError) ? "SUCCESS" : "FAILED");
	return (err == paNoError);
}

static int callback(const void *input, void *output, unsigned long fpb, const PaStreamCallbackTimeInfo *time_info, PaStreamCallbackFlags flags, void *user_data)
{
	return oscillator_cb(output, fpb, osc1);
}

int main(int argc, char **argv)
{
	double increment = 0.1f;

	if(argc >= 2)
	{
		increment = strtod(argv[1], NULL);
	}

	FILE *fp = fopen("music.wav", "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "failed to load music.wav\n");
		return -1;
	}

	//osc1 = oscillator_create(waveshape_sine_create(8192));
	//osc1 = oscillator_create(waveshape_wav_create(fp));
	osc1 = oscillator_create(waveshape_test_create());

	PaStream *stream;

	assert_pa_error(Pa_Initialize(), "initializing portaudio");
	assert_pa_error(Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, callback, NULL), "opening default stream");
	assert_pa_error(Pa_StartStream(stream), "starting stream");

	for(;;)
	{
		char c = fgetc(stdin);

		switch(c)
		{
			case '[':
				osc1->speed -= increment;
				break;
			case ']':
				osc1->speed += increment;
				break;
			case 'q':
				goto end;
		}
	}
end:

	assert_pa_error(Pa_Terminate(), "terminating portaudio");

	return 0;
}
