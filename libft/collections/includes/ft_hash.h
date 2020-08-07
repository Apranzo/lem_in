/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:06:04 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 15:06:04 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_STRING_H
# define HASH_STRING_H

#include <stddef.h>
#include <coreft.h>

size_t	ft_str_hash(pointer pointer);
size_t	string_nocase_hash(void *string);
size_t	int_hash(pointer pointer);
size_t	pointer_hash(pointer pointer);

#endif

