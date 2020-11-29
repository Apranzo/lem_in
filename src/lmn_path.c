/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:18:56 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void				free_path(t_pth *pth)
{
	lst_free(pth->rooms, NULL);
	free(pth);
}

void				free_pathes_wrapper(t_pths *pth)
{
	lst_free(pth->paths, (t_ffree) & free_path);
	free(pth->output);
	free(pth);
}
