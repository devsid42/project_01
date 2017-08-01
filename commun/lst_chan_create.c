/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_chan_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:51:47 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/24 19:47:43 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

t_chan		*lst_chan_create(char *name)
{
	t_chan			*node;

	if (!name)
		return (NULL);
	if (!(node = (t_chan *)ft_memalloc(sizeof(t_chan))))
		return (NULL);
	ft_memset(node->name, 0, CHAN_SIZE);
	ft_strncpy(node->name, name, CHAN_SIZE - 1);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}
