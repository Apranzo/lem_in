#include "lem_in.h"

int 				lgnl(int fd, char **line)
{
	int 			res;

	while ((res = ft_gnl(fd, line)) >= 0)
		if (*((uint16_t *)line) != 8995)
			break ;
	return (res);
}

int			is_num_valid(int value, char *str)
{
	char	*value_str;
	int		res;

	res = 0;
	value_str = ft_itoa(value);
	if (ft_strcmp(value_str, str + (str[0] == '+')) == 0)
		res = 1;
	if (value_str)
		free(value_str);
	return (res);
}

static int	validation(char **av, int **arr)
{
	size_t	i;

	i = 0;
	while (av[i])
	{
		(*arr)[i] = ft_atoi(av[i]);
		if (!is_num_valid((*arr)[i], av[i]) || is_num_duplicate(*arr, i))
			ft_error("Error\n", -1);
		i++;
	}
	return (i);
}


unsigned			parse_ants_amount()
{
	char
}

int					main(void)
{
	t_lemin			lemin;

	lemin.ants

}