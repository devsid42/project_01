/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_chan_del_by_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:44:37 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/24 19:44:42 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static int	is_first_last(t_chan **chans, t_chan *l)
{
	if (!l->prev && !l->next)
	{
		free(l);
		*chans = NULL;
		return (1);
	}
	return (0);
}

static int	is_first_not_last(t_chan **chans, t_chan *l)
{
	if (!l->prev && l->next)
	{
		l = l->next;
		free(l->prev);
		l->prev = NULL;
		*chans = l;
		return (1);
	}
	return (0);
}

static int	is_mid(t_chan *l)
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

static int	is_last(t_chan *l)
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

int			lst_chan_del_by_name(t_chan **chans, char *name)
{
	t_chan	*l;

	if (!chans || !name)
		return (0);
	l = *chans;
	while (l)
	{
		if (ft_strncmp(l->name, name, CHAN_SIZE) == 0)
		{
			if (is_first_last(chans, l) == 1)
				return (1);
			else if (is_first_not_last(chans, l) == 1)
				return (1);
			else if (is_mid(l) == 1)
				return (1);
			else if (is_last(l) == 1)
				return (1);
			else
				ft_printf(2, "[!] Unbelivable list case o.O\n");
			return (1);
		}
		l = l->next;
	}
	return (0);
}
