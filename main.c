#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "portaudio.h"
#include "oscillator.h"
#include "waveshape_sine.h"
#include "waveshape_wav.h"
#include "config.h"

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
	FILE *fp = fopen("music.wav", "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "failed to load music.wav\n");
		return -1;
	}

	//osc1 = oscillator_create(waveshape_sine_create(8192));
	osc1 = oscillator_create(waveshape_wav_create(fp));

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
				osc1->speed -= 0.05f;
				break;
			case ']':
				osc1->speed += 0.05f;
				break;
			case 'q':
				goto end;
		}
	}
end:

	assert_pa_error(Pa_Terminate(), "terminating portaudio");

	return 0;
}
