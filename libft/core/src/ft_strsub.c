/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 17:01:12 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/08 16:09:40 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!len || !(sub = ft_strnew(len)))
		return (NULL);
	return (ft_strncpy(sub, (s + start), len));
}
