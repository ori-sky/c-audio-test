#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "portaudio.h"

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

static unsigned char assert_pa_error(PaError err, const char * msg)
{
	fprintf(stderr, "%s [%s]\n", msg, (err == paNoError) ? "SUCCESS" : "FAILED");
	return (err == paNoError);
}

static int cb_gen_square(float * buffer, unsigned long frames, float frequency)
{
	static float phase = 0.0f;

	for(unsigned int i=0; i<frames; ++i)
	{
		buffer[i * 2 + 0] = ceil(sin(phase * frequency * 2.0f * 3.14159265358979f / SAMPLE_RATE));
		buffer[i * 2 + 1] = ceil(sin(phase * frequency * 2.0f * 3.14159265358979f / SAMPLE_RATE));

		++phase;
	}

	return 0;
}

static int callback(const void * input, void * output, unsigned long fpb, const PaStreamCallbackTimeInfo * time_info, PaStreamCallbackFlags flags, void * user_data)
{
	static float frequency = 261.625565f;
	float * buffer = (float *)output;
	return cb_gen_square(output, fpb, frequency += 0.01f);
}

int main(int argc, char ** argv)
{
	PaStream * stream;

	assert_pa_error(Pa_Initialize(), "initializing portaudio");
	assert_pa_error(Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, callback, NULL), "opening default stream");
	assert_pa_error(Pa_StartStream(stream), "starting stream");

	for(;;);

	assert_pa_error(Pa_Terminate(), "terminating portaudio");

	return 0;
}
