#include <coreft.h>

t_node *ft_lstappend(t_node **list, pointer data)
{
	t_node *rover;
	t_node *new;

	if (!list || !(new = ft_lstnew(data)))
		return (NULL);
	if (!*list)
		*list = new;
	else {
		rover = *list;
		while (rover->next)
			rover = rover->next;
		new->prev = rover;
		rover->next = new;
	}
	return (new);
}