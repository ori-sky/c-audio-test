#include <stdlib.h>
#include "node_oscillator.h"

struct node_s * node_oscillator_create(struct oscillator_s *osc)
{
	struct node_s *node = node_create(1, 1, &node_oscillator_cb);
	node->extra = osc;
	return node;
}

int node_oscillator_cb(struct node_s *node, unsigned long frames)
{
	struct oscillator_s *osc = node->extra;

	for(unsigned long frame=0; frame<frames; ++frame)
	{
		if(node->inputs[0].input != NULL)
		{
			osc->speed = (node->inputs[0].input->data[frame] + 1) / 2.0f;
		}

		node->outputs[0].data[frame] = oscillator_cb(osc);
	}

	return 0;
}
