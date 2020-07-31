///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   ft_nds_fltr.c                                      :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2019/04/18 23:39:59 by cshinoha          #+#    #+#             */
///*   Updated: 2020/07/04 15:45:00 by cshinoha         ###   ########.ru       */
///*                                                                            */
///* ************************************************************************** */
//
//#include <coreft.h>
//
//t_node		*ft_nds_fltr(t_node *lst, t_node *(*f)(t_node *elem))
//{
//	t_node	*first;
//	t_node	*new;
//
//	new = f(lst);
//	first = new;
//	lst = lst->next;
//	while (lst)
//	{
//		new->next = f(lst);
//		lst = lst->next;
//		new = new->next;
//	}
//	return (first);
//}