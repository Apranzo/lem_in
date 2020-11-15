
#include "../includes/lem_in.h"


t_edge				*edg_new(t_room *dst)
{
	t_edge			*new;

	if (!(new = ft_memalloc(sizeof(t_edge))))
		ft_error("Error", -1);
	new->dts = dst;
	return (new);
}

int 				edge_eq(t_edge *ed1, t_edge *ed2)
{
	return (ed1->dts == ed2->dts);
}