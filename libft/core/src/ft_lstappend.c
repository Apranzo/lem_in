#include <coreft.h>

t_node *ft_node_append(t_node **node, pointer data)
{
	t_node *rover;
	t_node *new;

	if (!node || !(new = ft_lstnew(data)))
		return (NULL);
	if (!*node)
		*node = new;
	else {
		rover = *node;
		while (rover->next)
			rover = rover->next;
		new->prev = rover;
		rover->next = new;
	}
	return (new);
}