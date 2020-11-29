/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:35:43 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../includes/coreft.h"

char		*ft_strcat(char *s1, const char *s2)
{
	int		start;
	char	*src;

	src = (char *)s2;
	start = ft_strlen(s1);
	while (*src)
		s1[start++] = *(src++);
	s1[start] = '\0';
	return (s1);
}
