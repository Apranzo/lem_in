/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:06:04 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/08 19:23:41 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASH_H
# define FT_HASH_H

# include "../../core/includes/coreft.h"

size_t	ft_str_hash(t_pntr pointer);
size_t	int_hash(t_pntr pointer);
size_t	pointer_hash(t_pntr pointer);

#endif
