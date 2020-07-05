/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 23:58:48 by cmeowth           #+#    #+#             */
/*   Updated: 2020/07/04 15:45:01 by cshinoha         ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

char		**ft_strnew2d(size_t size)
{
	char	**str;

	if (!(str = (char **)ft_memalloc(sizeof(char *) * size + 1)))
		return (NULL);
	return (str);
}
