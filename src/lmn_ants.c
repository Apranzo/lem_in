#include "includes/lem_in.h"

void				create_ants(t_lemin *lem)
{
	t_lst			*ants;
	t_ant 			*ant;
	size_t 			num;

	num = lem->amount;
	ants = lst_new();
	while (num)
	{
		if (!(ant = malloc(sizeof(t_ant))))
			ft_error("Error\n", -1);
		ant->room = NULL;
		ant->finished = 0;
		ant->started = 0;
		ant->number = num;
		lst_append(ants, ant);
		num--;
	}
	lem->ants = ants;
	if (!(lem->qu = qu_by_lst(lem->ants)))
		ft_error("Error\n", -1);
}