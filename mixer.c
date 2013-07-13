#include <stdlib.h>
#include "mixer.h"

struct mixer_s * mixer_create(void)
{
	struct mixer_s *mixer = malloc(sizeof(struct mixer_s));
	mixer->output_node = node_create(2, 0, &mixer_output_node_cb);
	mixer->output_node->extra = malloc(sizeof(float) * 2);
	return mixer;
}

int mixer_cb(struct mixer_s *mixer, float *output_buffer, unsigned long frames)
{
	/*for(unsigned long frame=0; frame<frames; ++frame)
	{
		mixer_unprocess_node(mixer->output_node);
		mixer_process_node(mixer->output_node);

		float *extra = mixer->output_node->extra;
		output_buffer[frame * 2 + 0] = extra[0];
		output_buffer[frame * 2 + 1] = extra[1];
	}*/

	mixer_unprocess_node(mixer->output_node);
	mixer->output_node->extra = output_buffer;
	mixer_process_node(mixer->output_node, frames);

	return 0;
}

int mixer_process_node(struct node_s *node, unsigned long frames)
{
	if(node->processed == 0)
	{
		for(unsigned char i=0; i<node->num_inputs; ++i)
		{
			if(node->inputs[i].input != NULL)
			{
				mixer_process_node(node->inputs[i].input->node, frames);
			}
		}

		node->cb(node, frames);
		node->processed = 1;
	}

	return 0;
}

int mixer_unprocess_node(struct node_s *node)
{
	for(unsigned char i=0; i<node->num_inputs; ++i)
	{
		if(node->inputs[i].input != NULL)
		{
			mixer_unprocess_node(node->inputs[i].input->node);
		}
	}

	node->processed = 0;
	return 0;

}

int mixer_output_node_cb(struct node_s *node, unsigned long frames)
{
	float *extra = node->extra;
	for(unsigned long frame=0; frame<frames; ++frame)
	{
		extra[frame * 2 + 0] = node->inputs[0].input->data[frame];
		extra[frame * 2 + 1] = node->inputs[1].input->data[frame];
	}

	return 0;
}
