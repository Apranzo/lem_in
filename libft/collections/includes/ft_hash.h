/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:06:04 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/08 11:31:33 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_STRING_H
# define HASH_STRING_H

# include <coreft.h>

size_t	ft_str_hash(t_pntr pointer);
size_t	string_nocase_hash(void *string);
size_t	int_hash(t_pntr pointer);
size_t	pointer_hash(t_pntr pointer);

#endif

