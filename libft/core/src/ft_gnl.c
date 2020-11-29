/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 17:47:39 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coreft.h>

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

static void					freenode(t_node *ll, t_node **l)
{
	t_stmt					*s;

	s = ll->data;
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
	ft_bzero(ll, sizeof(t_node));
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

static t_node				*init_static_list(t_node **l, int fd)
{
	t_node					*tmp;
	t_stmt					*s;

	tmp = *l;
	while (tmp)
	{
		s = (t_stmt *)tmp->data;
		if (s->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(s = stmnew(fd)))
		return (NULL);
	ft_node_prepend(l, s);
	return (*l);
}

int							ft_gnl(const int fd, char **line)
{
	static t_node			*l;
	t_node					*ll;
	int						ret;
	char					buff[BUFF_SIZE + 1];
	char					*tmp;

	ll = NULL;
	if (fd < 0 || !line || !(ll = init_static_list(&l, fd)))
		return (-1);
	while (!ft_strchr(((t_stmt *)ll->data)->res, '\n') &&
						(ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = ((t_stmt *)ll->data)->res;
		((t_stmt *)ll->data)->res =
				ft_strjoin(((t_stmt *)ll->data)->res, buff);
		free(tmp);
	}
	if ((ret = get_line(line, ((t_stmt *)ll->data), ret)) <= 0 || !line)
		freenode(ll, &l);
	return (ret);
}
