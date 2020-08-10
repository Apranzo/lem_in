/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:19:05 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/10 19:54:48 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			print_input(const t_lemin *lem)
{
	t_itr		*itr;

	itr = lst_itr_load(lem->raw, NULL, NULL);
	while (itr_has_more(itr))
		ft_printf("%s\n", itr_next(itr));
	itr_free(itr);
}

void			print_res(t_lemin *lem)
{
	t_itr		*itr;
	t_str_bld	*bld;
	char		*output;

	lmn_prepare_paths(lem);
	itr = lst_itr_load(lem->ants, NULL, NULL);
	if (!(bld = sb_create("\n")) || (!bld->len))
		ft_error("Error", -1);
	lmn_produce_output(lem, itr, bld);
	if (!(output = sb_concat(bld)))
		ft_error("Error", -1);
	write(1, output, bld->len);
	free(output);
	sb_free(bld);
	itr_free(itr);
}
