/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:51:18 by cshinoha          #+#    #+#             */
/*   Updated: 2020/07/04 15:45:00 by cshinoha         ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../includes/coreft.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	char	*stack;
	char	*ref;

	stack = (char *)haystack;
	ref = (char *)needle;
	if (!*needle)
		return (stack);
	while (*stack)
	{
		if (ft_strstartwith(ref, stack))
			return (stack);
		stack++;
	}
	return (NULL);
}
