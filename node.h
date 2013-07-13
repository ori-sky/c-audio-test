#ifndef NODE_H
#define NODE_H

#include "config.h"

struct node_s;
struct node_input_s;
struct node_output_s;

typedef int (*node_callback_t)(struct node_s *, unsigned long);

struct node_s
{
	unsigned char num_inputs;
	unsigned char num_outputs;
	struct node_input_s *inputs;
	struct node_output_s *outputs;
	node_callback_t cb;
	void *extra;
	unsigned char processed;
};

struct node_input_s
{
	struct node_s *node;
	struct node_output_s *input;
	char * id;
};

struct node_output_s
{
	struct node_s *node;
	float data[FRAMES_PER_BUFFER];
	char * id;
};

extern struct node_s * node_create(unsigned char num_inputs, unsigned char num_outputs, node_callback_t cb);
extern int node_link(struct node_output_s *out, struct node_input_s *in);

#endif
