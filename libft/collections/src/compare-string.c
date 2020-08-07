/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare-string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:06:46 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 15:06:46 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/compare-string.h"

int			string_equal(void *string1, void *string2)
{
	return (!ft_strcmp((char *) string1, (char *) string2));
}

int			string_compare(void *string1, void *string2)
{
	int		result;

	result = ft_strcmp((char *) string1, (char *) string2);
	if (result < 0)
		return (-1);
	if (result > 0)
		return (1);
	return (0);
}

