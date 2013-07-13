#ifndef NODE_OSCILLATOR_H
#define NODE_OSCILLATOR_H

#include "node.h"
#include "oscillator.h"

extern struct node_s * node_oscillator_create(struct oscillator_s *osc);
extern int node_oscillator_cb(struct node_s *node, unsigned long frames);

#endif
