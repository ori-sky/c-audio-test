#include <stdlib.h>
#include "node.h"

struct node_s * node_create(unsigned char num_inputs, unsigned char num_outputs, node_callback_t cb)
{
	struct node_s *node = malloc(sizeof(struct node_s));
	node->num_inputs = num_inputs;
	node->num_outputs = num_outputs;
	node->inputs = malloc(sizeof(struct node_input_s) * num_inputs);
	node->outputs = malloc(sizeof(struct node_output_s) * num_outputs);
	node->cb = cb;
	node->extra = NULL;

	unsigned char i;

	for(i=0; i<num_inputs; ++i)
	{
		node->inputs[i].node = node;
	}

	for(i=0; i<num_outputs; ++i)
	{
		node->outputs[i].node = node;
	}

	return node;
}

int node_link(struct node_output_s *out, struct node_input_s *in)
{
	in->input = out;
	return 0;
}
