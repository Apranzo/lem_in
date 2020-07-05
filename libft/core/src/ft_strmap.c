/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 23:27:17 by cshinoha          #+#    #+#             */
/*   Updated: 2020/07/04 15:45:00 by cshinoha         ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*mapped;
	size_t	index;
	size_t	len;

	len = ft_strlen(s);
	index = 0;
	mapped = ft_strnew(len);
	if (!mapped)
		return (NULL);
	while (index < len)
	{
		mapped[index] = f(s[index]);
		index++;
	}
	return (mapped);
}
