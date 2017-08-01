/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_chan_add_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:51:45 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/24 19:44:55 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

int			lst_chan_add_end(t_chan **main_lst, t_chan *new_node)
{
	t_chan	*l;

	if (!main_lst)
		return (-1);
	if (!*main_lst)
	{
		*main_lst = new_node;
		return (0);
	}
	l = *main_lst;
	while (l->next)
		l = l->next;
	new_node->prev = l;
	l->next = new_node;
	return (0);
}
