/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:24:28 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"
#include <stdlib.h>

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size1;
	size_t	size2;
	char	*new;

	if (!s1 && !s2)
		return (NULL);
	size1 = s1 ? ft_strlen(s1) : 0;
	size2 = s2 ? ft_strlen(s2) : 0;
	new = ft_strnew(size1 + size2);
	ft_strcpy(new, s1);
	ft_strncat(new, s2, size2);
	return (new);
}
