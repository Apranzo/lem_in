/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntwords.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 14:17:42 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

int			ft_cntwords(char const *s, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (s && s[i] != '\0')
	{
		if (!ft_isseparator(s[i], c))
		{
			words++;
			while (s[i] != '\0' && !ft_isseparator(s[i], c))
				i++;
		}
		i += s[i] != '\0';
	}
	return (words);
}
