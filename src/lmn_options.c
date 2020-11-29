/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 17:32:53 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 15:50:07 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_opt	*opt_cnst(void)
{
	t_opt		*opt;

	if (!(opt = ft_memalloc(sizeof(t_opt))))
		ft_error("Malloc error", -1);
	opt->out = 1;
	opt->logfile = -1;
	return (opt);
}

static int		open_output(char **const *av, t_opt *opt)
{
	opt->out = open(*(*av + 1), O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	if (opt->out < 0)
		ft_error("Open output file error", -1);
	return (opt->out);
}

static int		open_log(char **const *av, t_opt *opt)
{
	opt->logfile = open(*(*av + 1), O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	if (opt->logfile < 0)
		ft_error("Open log file error", -1);
	opt->verbose = 1;
	return (1);
}

t_opt			*find_opt(int *ac, char ***av)
{
	t_opt		*opt;

	opt = opt_cnst();
	while (**av && ***av == '-')
	{
		if ((**av)[1] == 'v')
			opt->verbose = 1;
		else if ((**av)[1] == 'o')
			open_output(av, opt) && (*av)++ && (*ac)--;
		else if ((**av)[1] == 'l')
			open_log(av, opt) && (*av)++ && (*ac)--;
		else if ((**av)[1] == 'd')
			opt->dsc = 1;
		else if ((**av)[1] == 'c')
			(opt->color = 1);
		else if ((**av)[1] == 'r')
			(opt->req = 1);
		else
			return (opt);
		(*av)++;
	}
	return (opt);
}
