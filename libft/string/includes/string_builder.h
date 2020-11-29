/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:34:11 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_BUILDER_H
# define STRING_BUILDER_H

# include "../../core/includes/coreft.h"
# include "../../collections//includes/collections.h"

typedef struct				s_string
{
	char					*str;
	int						length;
}							t_str;

typedef struct				s_sting_builder
{
	t_lst					*fragments;
	size_t					len;
	char					*concated;
}							t_str_bld;

void						sb_repl_by_ind(t_str_bld *bld, size_t ind, char c);
char						sb_by_ind(t_str_bld *bld, size_t ind);
t_str_bld					*sb_create(char *s);
int							sb_empty(t_str_bld *sb);
int							sb_append_len(t_str_bld *sb, char *str, size_t len);
int							sb_append(t_str_bld *sb, char *str);
char						*sb_concat(t_str_bld *sb);
void						sb_reset(t_str_bld *sb);
void						sb_free(t_str_bld *sb);

#endif
