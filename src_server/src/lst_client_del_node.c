/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_client_del_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:43:10 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/27 19:04:45 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static int	is_first_last(t_client **cnt, t_client *l)
{
	if (!l->prev && !l->next)
	{
		free(l);
		*cnt = NULL;
		return (1);
	}
	return (0);
}

static int	is_first_not_last(t_client **cnt, t_client *l)
{
	if (!l->prev && l->next)
	{
		l = l->next;
		free(l->prev);
		l->prev = NULL;
		*cnt = l;
		return (1);
	}
	return (0);
}

static int	is_mid(t_client *l)
{
	if (l->prev && l->next)
	{
		l->prev->next = l->next;
		l->next->prev = l->prev;
		free(l);
		return (1);
	}
	return (0);
}

static int	is_last(t_client *l)
{
	if (l->prev && !l->next)
	{
		l = l->prev;
		free(l->next);
		l->next = NULL;
		return (1);
	}
	return (0);
}

int			lst_client_del_node(t_client **cnt, int sock)
{
	t_client	*l;

	if (!cnt)
		return (-1);
	l = *cnt;
	while (l)
	{
		if (l->sock == sock)
		{
			lst_chan_delete_all(&l->chans);
			if (is_first_last(cnt, l) == 1)
				return (1);
			else if (is_first_not_last(cnt, l) == 1)
				return (1);
			else if (is_mid(l) == 1)
				return (1);
			else if (is_last(l) == 1)
				return (1);
			return (-1);
		}
		l = l->next;
	}
	ft_printf(2, "[!] Client not found in del node: %d\n", sock);
	return (0);
}
