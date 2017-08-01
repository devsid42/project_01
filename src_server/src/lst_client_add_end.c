/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_client_add_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 19:57:05 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/24 23:45:50 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

int		lst_client_add_end(t_client **cnt, t_client *new_node)
{
	t_client	*l;

	if (!cnt)
		return (-1);
	if (!*cnt)
	{
		*cnt = new_node;
		return (0);
	}
	l = *cnt;
	while (l->next)
		l = l->next;
	new_node->prev = l;
	l->next = new_node;
	return (0);
}
