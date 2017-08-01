/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_chan_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 23:36:28 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/01 23:31:16 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static void	put_history(t_chan *l)
{
	while (l)
	{
		ft_printf(1, "%s ", l->name);
		l = l->next;
	}
}

static void	put_anti_history(t_chan *l)
{
	while (l->next)
		l = l->next;
	while (l)
	{
		ft_printf(1, "%s ", l->name);
		l = l->prev;
	}
}

void		lst_chan_put(t_chan *chans, char *msg, int dir)
{
	t_chan	*l;

	if (!chans || !msg)
		return ;
	ft_printf(1, "%s", msg);
	l = chans;
	if (dir == 0)
		put_history(l);
	else if (dir == 1)
		put_anti_history(l);
	ft_printf(1, "\n");
}
