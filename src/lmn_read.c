/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:19:17 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/11 14:00:15 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int			input_filter_predict(char *line)
{
	return (ft_strncmp(line, JAIL, 1)
			|| (!ft_strcmp(line, START) || !ft_strcmp(line, END)));
}

int					read_intput(int fd, t_lemin *lem)
{
	char			*line;
	int				res;

	line = NULL;
	while ((res = ft_gnl(fd, &line)) > 0 && line)
	{
		if (!lst_append(lem->raw, line))
			ft_error("read_input Error allocation\n", -1);
		line = NULL;
	}
	if (line)
		if (!lst_append(lem->raw, line))
			ft_error("read_input Error allocation\n", -1);
	if (res < 0	|| !lem->raw->length)
		ft_error("Error", -2);
	if ( !(lem->filtred = lst_itr_load(lem->raw, NULL,
										(t_fprdct)input_filter_predict)))
		ft_error("filtered alloc error", -1);
	return (!res);
}
