/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 17:00:50 by cshinoha          #+#    #+#             */
/*   Updated: 2020/07/04 15:45:00 by cshinoha         ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include <coreft.h>

//static	t_stmt				*stmnew(int fd)
//{
//	t_stmt					*statement;
//
//	if (!(statement = (t_stmt *)malloc(sizeof(t_stmt))))
//		return (NULL);
//	if (!(statement->res = ft_strnew(0)))
//		return (NULL);
//	statement->fd = fd;
//	return (statement);
//}
//
//static void					freenode(t_node *ll, t_node **l)
//{
//	t_stmt					*s;
//
//	s = ll->data;
//	free(s->res);
//	free(s);
//	if (ll->next)
//		ll->next->prev = ll->prev;
//	if (ll->prev)
//		ll->prev->next = ll->next;
//	if (ll == *l && ll->next)
//		*l = ll->next;
//	else if (ll == *l)
//		*l = NULL;
//	ft_bzero(ll, sizeof(t_node));
//	free(ll);
//}
//
//static int					get_line(char **line, t_stmt *s, int ret)
//{
//	char					*tmp;
//	int						len;
//
//	if (!(len = 0) && ret < 0)
//		return (-1);
//	else if (ret == 0 && !*s->res)
//		return (0);
//	while (s->res[len] != '\n' && s->res[len] != '\0')
//		len++;
//	if (s->res[len] == '\n')
//	{
//		*line = ft_strsub(s->res, 0, len);
//		tmp = s->res;
//		s->res = ft_strdup(s->res + len + 1);
//		free(tmp);
//	}
//	else if (s->res[len] == '\0')
//	{
//		*line = ft_strdup(s->res);
//		tmp = s->res;
//		s->res = ft_strdup(s->res + len);
//		free(tmp);
//		return (0);
//	}
//	return (1);
//}
//
//static t_node				*init_static_list(t_node **l, int fd)
//{
//	t_node					*tmp;
//	t_stmt					*s;
//
//	tmp = *l;
//	while (tmp)
//	{
//		s = (t_stmt *)tmp->data;
//		if (s->fd == fd)
//			return (tmp);
//		tmp = tmp->next;
//	}
//	if (!(s = stmnew(fd)))
//		return (NULL);
//	ft_node_prepend(l, s);
//	return (*l);
//}
//
//int							ft_gnl(const int fd, char **line)
//{
//	static t_node			*l;
//	t_node					*ll;
//	int						ret;
//	char					buff[BUFF_SIZE + 1];
//	char					*tmp;
//
//	ll = NULL;
//	if (fd < 0 || line == NULL || !(ll = init_static_list(&l, fd)))
//		return (-1);
//	while (!ft_strchr(((t_stmt *)ll->data)->res, '\n') &&
//						(ret = read(fd, buff, BUFF_SIZE)) > 0)
//	{
//		buff[ret] = '\0';
//		tmp = ((t_stmt *)ll->data)->res;
//		((t_stmt *)ll->data)->res =
//				ft_strjoin(((t_stmt *)ll->data)->res, buff);
//		free(tmp);
//	}
//	if ((ret = get_line(line, ((t_stmt *)ll->data), ret)) <= 0)
//		freenode(ll, &l);
//	return (ret);
//}


typedef struct		s_file
{
	int				fd;
	char			*str;
	struct s_file	*next;
}					t_file;

#include <unistd.h>


static char	*ft_strchrs(const char *s, int c)
{
	if (!s)
		return (NULL);
	return (ft_strchr(s, c));
}

static char	*ft_strsubchr(const char *s, char c)
{
	char	*ptr;

	if (!(ptr = ft_strchrs(s, c)))
		return (NULL);
	return (ft_strsub(s, 0, ptr - s));
}

static t_file	*new_file(const int fd)
{
	t_file *new;

	if ((new = (t_file *)ft_memalloc(sizeof(t_file))))
	{
		new->fd = fd;
		new->str = NULL;
	}
	return (new);
}

static t_file	*get_file(const int fd, t_file **head)
{
	t_file *lst;

	if (!(*head))
		return (*head = new_file(fd));
	lst = *head;
	while (lst->next && lst->fd != fd)
		lst = lst->next;
	return ((lst->fd == fd) ? lst : (lst->next = new_file(fd)));
}

static int		str_divide(char **str, char **line)
{
	char	*new;
	char	*div;

	if (!(*line = ft_strsubchr(*str, '\n')))
		return (-1);
	div = ft_strchrs(*str, '\n');
	div++;
	if (!ft_strlen(div))
	{
		free(*str);
		*str = NULL;
		return (1);
	}
	new = ft_strdup(div);
	free(*str);
	*str = new;
	return ((new) ? 1 : -1);
}

int				ft_gnl(const int fd, char **line)
{
	static t_file	*head = NULL;
	t_file			*f;
	char			buff[BUFF_SIZE + 1];
	ssize_t			size;
	char			*tmp;

	if (fd < 0 || !line || read(fd, buff, 0) < 0 || !(f = get_file(fd, &head)))
		return (-1);
	while (!ft_strchrs(f->str, '\n'))
	{
		if (!(size = read(fd, buff, BUFF_SIZE)))
		{
			if (!(*line = f->str))
				return (0);
			f->str = NULL;
			return (1);
		}
		buff[size] = '\0';
		tmp = f->str;
		f->str = ft_strjoin(f->str, buff);
		free(tmp);
		if (!f->str)
			return (-1);
	}
	return (str_divide(&(f->str), line));
}