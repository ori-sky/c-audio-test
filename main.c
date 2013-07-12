#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "portaudio.h"
#include "config.h"
#include "node.h"
#include "node_oscillator.h"

#include "waveshape_sine.h"
#include "waveshape_wav.h"
#include "waveshape_test.h"

struct node_s * n;

static unsigned char assert_pa_error(PaError err, const char *msg)
{
	fprintf(stderr, "%s [%s]\n", msg, (err == paNoError) ? "SUCCESS" : "FAILED");
	return (err == paNoError);
}

static int callback(const void *input, void *output, unsigned long fpb, const PaStreamCallbackTimeInfo *time_info, PaStreamCallbackFlags flags, void *user_data)
{
	//return n->cb(n);
	return oscillator_cb(output, fpb, n->extra);
}

int main(int argc, char **argv)
{
	FILE *fp = fopen("music.wav", "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "failed to load music.wav\n");
		return -1;
	}

	n = node_oscillator_create(oscillator_create(waveshape_wav_create(fp)));

	PaStream *stream;

	assert_pa_error(Pa_Initialize(), "initializing portaudio");
	assert_pa_error(Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, callback, NULL), "opening default stream");
	assert_pa_error(Pa_StartStream(stream), "starting stream");

	for(unsigned char running=1; running;)
	{
		char c = fgetc(stdin);

		switch(c)
		{
			case 'q':
				running = 0;
		}
	}

	assert_pa_error(Pa_Terminate(), "terminating portaudio");

	return 0;
}
