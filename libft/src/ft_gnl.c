/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 17:00:50 by cshinoha          #+#    #+#             */
/*   Updated: 2020/06/11 17:00:50 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static	t_stmt				*stmnew(int fd)
{
	t_stmt					*statement;

	if (!(statement = (t_stmt *)malloc(sizeof(t_stmt))))
		return (NULL);
	if (!(statement->res = ft_strnew(0)))
		return (NULL);
	statement->fd = fd;
	return (statement);
}

static void					freenode(t_list *ll, t_list **l)
{
	t_stmt					*s;

	s = ll->content;
	free(s->res);
	free(s);
	if (ll->next)
		ll->next->prev = ll->prev;
	if (ll->prev)
		ll->prev->next = ll->next;
	if (ll == *l && ll->next)
		*l = ll->next;
	else if (ll == *l)
		*l = NULL;
	ft_bzero(ll, sizeof(t_list));
	free(ll);
}

static int					get_line(char **line, t_stmt *s, int ret)
{
	char					*tmp;
	int						len;

	if (!(len = 0) && ret < 0)
		return (-1);
	else if (ret == 0 && !*s->res)
		return (0);
	while (s->res[len] != '\n' && s->res[len] != '\0')
		len++;
	if (s->res[len] == '\n')
	{
		*line = ft_strsub(s->res, 0, len);
		tmp = s->res;
		s->res = ft_strdup(s->res + len + 1);
		free(tmp);
	}
	else if (s->res[len] == '\0')
	{
		*line = ft_strdup(s->res);
		tmp = s->res;
		s->res = ft_strdup(s->res + len);
		free(tmp);
		return (0);
	}
	return (1);
}

static t_list				*init_static_list(t_list **l, int fd)
{
	t_list					*tmp;
	t_stmt					*s;

	tmp = *l;
	while (tmp)
	{
		s = (t_stmt *)tmp->content;
		if (s->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(s = stmnew(fd)))
		return (NULL);
	ft_lstpush(l, s, sizeof(t_stmt));
	free(s);
	return (*l);
}

int							ft_gnl(const int fd, char **line)
{
	static t_list			*l;
	t_list					*ll;
	int						ret;
	char					buff[BUFF_SIZE + 1];
	char					*tmp;

	ll = NULL;
	if (fd < 0 || line == NULL || !(ll = init_static_list(&l, fd)))
		return (-1);
	while (!ft_strchr(((t_stmt *)ll->content)->res, '\n') &&
						(ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = ((t_stmt *)ll->content)->res;
		((t_stmt *)ll->content)->res =
				ft_strjoin(((t_stmt *)ll->content)->res, buff);
		free(tmp);
	}
	if ((ret = get_line(line, ((t_stmt *)ll->content), ret)) <= 0)
		freenode(ll, &l);
	return (ret);
}
