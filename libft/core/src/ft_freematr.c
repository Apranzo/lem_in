/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freematr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:04:01 by hchau             #+#    #+#             */
/*   Updated: 2020/07/04 15:45:00 by cshinoha         ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_freematr(char **matr)
{
	size_t		i;

	i = 0;
	while (matr && matr[i])
	{
		free(matr[i]);
		matr[i++] = NULL;
	}
	free(matr);
	return (NULL);
}
