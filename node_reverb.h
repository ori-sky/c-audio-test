#ifndef NODE_REVERB_H
#define NODE_REVERB_H

#include "node.h"

struct node_reverb_data_s
{
	float factor;
	int buffer_size;
	int buffer_head;
	float *buffer;
};

extern struct node_s * node_reverb_create(int buffer_size, float factor);
extern struct node_reverb_data_s * node_reverb_data_create(int buffer_size, float factor);
extern int node_reverb_cb(struct node_s *node, unsigned long frames);

#endif
