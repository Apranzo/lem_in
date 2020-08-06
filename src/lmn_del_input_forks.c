#include "includes/lem_in.h"

static	int 		del_input_forks(t_room	*room) // TODO What?
{
	t_node			*node;
	pointer			data;

	node = room->in->first;
	while (!room->required && node)
	{
		if (!((t_room*)node->data)->required && room->in->length != 1)
		{
			data = node->data;
			lst_rm_entry(room->in, node);
			lst_rm_data(((t_room*)data)->out, (f_equal) &room_equals, room);
			return (1);
		}
		else
			node = node->next;
	}
	return (0);
}

void				lmn_del_input_forks(const t_lst *lst)
{
	t_node		*node;

	node = lst->first;
	while (node)
	{
		if (del_input_forks(node->data))
		{
			lmn_del_dead_end(lst);
			node = lst->first;
		}
		else
			node = node->next;
	}
}
