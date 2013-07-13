#ifndef MIXER_H
#define MIXER_H

#include "node.h"

struct mixer_s
{
	struct node_s *output_node;
};



extern struct mixer_s * mixer_create(void);
extern int mixer_cb(struct mixer_s *mixer, float *output_buffer, unsigned long frames);
extern int mixer_process_node(struct node_s *node, unsigned long frames);
extern int mixer_unprocess_node(struct node_s *node);
extern int mixer_output_node_cb(struct node_s *node, unsigned long frames);

#endif
