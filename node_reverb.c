#include <stdlib.h>
#include <math.h>
#include "node_reverb.h"

struct node_s * node_reverb_create(int buffer_size, float factor)
{
	struct node_s *node = node_create(1, 1, &node_reverb_cb);
	struct node_reverb_data_s *data = node_reverb_data_create(buffer_size, factor);
	node->extra = data;
	return node;
}

struct node_reverb_data_s * node_reverb_data_create(int buffer_size, float factor)
{
	struct node_reverb_data_s *data = malloc(sizeof(struct node_reverb_data_s));
	data->factor = factor;
	data->buffer_size = buffer_size;
	data->buffer_head = 0;
	data->buffer = calloc(1, sizeof(float) * buffer_size);
	return data;
}

int node_reverb_cb(struct node_s *node, unsigned long frames)
{
	struct node_reverb_data_s *data = node->extra;

	for(unsigned long frame=0; frame<frames; ++frame)
	{
		data->buffer[data->buffer_head] = 0;

		if(node->inputs[0].input != NULL)
		{
			data->buffer[data->buffer_head] = node->inputs[0].input->data[frame];
		}

		int index;
		float value;

		for(int i=0; i<data->buffer_size; ++i)
		{
			index = data->buffer_head - i;
			if(index < 0) index += data->buffer_size;

			//value += data->buffer[index];
			//data->buffer[index] *= data->factor;
		}

		//node->outputs[0].data[frame] = value;
		node->outputs[0].data[frame] = node->inputs[0].input->data[frame];

		++data->buffer_head;
		if(data->buffer_head >= data->buffer_size) data->buffer_head -= data->buffer_size;
	}

	return 0;
}
