/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfrjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:24:28 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

char		*ft_strfrjoin(char *s1, char *s2)
{
	size_t	size1;
	size_t	size2;
	char	*new;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	new = ft_strnew(size1 + size2);
	ft_strcpy(new, s1);
	ft_strncat(new, s2, size2);
	free(s1);
	free(s2);
	return (new);
}
