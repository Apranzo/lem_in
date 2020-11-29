/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:51:51 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

char	*ft_strtrim(char const *s)
{
	size_t len;

	while (*s && (*s == ' ' || *s == '\t' || *s == '\n'))
		s++;
	if (!*s)
		return ("");
	len = 0;
	while (*s || *s--)
		s++ && len++;
	while (*s && (*s == ' ' || *s == '\n' || *s == '\t'))
		s-- && len--;
	return (ft_strsub(s - len + 1, 0, len));
}
