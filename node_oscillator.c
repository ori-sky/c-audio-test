#include <stdlib.h>
#include "node_oscillator.h"

struct node_s * node_oscillator_create(struct oscillator_s *osc)
{
	struct node_s *node = node_create(0, 1, &node_oscillator_cb);
	node->extra = osc;
	return node;
}

int node_oscillator_cb(struct node_s *node)
{
	return 0;
}
