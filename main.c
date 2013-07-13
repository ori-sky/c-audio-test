#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "portaudio.h"
#include "config.h"
#include "mixer.h"
#include "node.h"
#include "node_oscillator.h"
#include "node_reverb.h"

#include "waveshape_sine.h"
#include "waveshape_wav.h"
#include "waveshape_test.h"

unsigned char *lock;
struct mixer_s * mixer;

static unsigned char assert_pa_error(PaError err, const char *msg)
{
	fprintf(stderr, "%s [%s]\n", msg, (err == paNoError) ? "SUCCESS" : "FAILED");
	return (err == paNoError);
}

static int callback(const void *input, void *output, unsigned long fpb, const PaStreamCallbackTimeInfo *time_info, PaStreamCallbackFlags flags, void *user_data)
{
	if(*lock == 0)
	{
		*lock = 1;
		mixer_cb(mixer, output, fpb);
		*lock = 0;
	}
	return 0;
}

int main(int argc, char **argv)
{
	lock = malloc(sizeof(unsigned char));
	*lock = 0;

	FILE *fp = fopen("music.wav", "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "failed to load music.wav\n");
		return -1;
	}

	mixer = mixer_create();

	struct node_s * n_sine = node_oscillator_create(oscillator_create(waveshape_sine_create(512)));
	struct node_s * n_music = node_oscillator_create(oscillator_create(waveshape_wav_create(fp)));
	//struct node_s * n_reverb = node_reverb_create(256, 0.5f);

	((struct oscillator_s *)n_sine->extra)->frequency = 1.0f;

	//node_link(&n_sine->outputs[0], &n_music->inputs[0]);
	//node_link(&n_music->outputs[0], &n_reverb->inputs[0]);
	node_link(&n_music->outputs[0], &mixer->output_node->inputs[0]);
	node_link(&n_music->outputs[0], &mixer->output_node->inputs[1]);

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
