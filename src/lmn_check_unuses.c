#include "includes/lem_in.h"

static	void 		check_unuses(t_room	*room)
{
	t_node			*node;
	t_node			*next;
	pointer			*data;

	node = room->out->first;
	while (node)
	{
		next = node->next;
		data = node->data;
		if (room->asc_level < 0)
		{
			lst_rm_data(((t_room *) data)->out, (f_equal) &room_equals, room);
			lst_rm_data(((t_room *) data)->in, (f_equal) &room_equals, room);
			lst_rm_data(room->in, (f_equal) &room_equals, data);
			lst_rm_data(room->out, (f_equal) &room_equals, data);
		}
		else if (((t_room*)node->data)->asc_level == room->asc_level)
		{
			lst_rm_data(room->in, (f_equal) &room_equals, data);
			lst_rm_data(((t_room *) data)->out, (f_equal) &room_equals, room);
			lst_rm_data(room->out, (f_equal) &room_equals, data);
			lst_rm_data(((t_room *) data)->in, (f_equal) &room_equals, room);
		}
		node = next;
	}
}

void				lmn_check_unuses(const t_lst *lst)
{
	t_node		*node;

	node = lst->first;
	while (node)
	{
		check_unuses(node->data);
		node = node->next;
	}
}
