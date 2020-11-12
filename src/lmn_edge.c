#include "../includes/lem_in.h"

void				free_egde(t_edge *edge)
{
	free(edge);
}

int				edge_equals(t_edge *edge1, t_edge *edge2)
{
	return (room_equals(edge1->dest, edge2->dest));
}