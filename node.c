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
	return node;
}

void node_link(struct node_output_s *out, struct node_input_s *in)
{
	in->input = out;
}
