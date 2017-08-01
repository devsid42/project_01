/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_client_channel_user.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 12:30:53 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 01:24:27 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

int			lst_client_channel_user_nb(t_client *cnt, char *chan)
{
	t_client	*l;
	t_chan		*lst_chan;
	int			user;

	if (!cnt || !chan)
		return (-1);
	l = cnt;
	user = 0;
	while (l)
	{
		if (l->chans)
		{
			lst_chan = l->chans;
			while (lst_chan)
			{
				if (ft_sec_strnccmp(\
								lst_chan->name, chan, CHAN_SIZE - 1) == SAME)
					user += 1;
				lst_chan = lst_chan->next;
			}
		}
		l = l->next;
	}
	return (user);
}

static int	foreach_user_chans(t_client *cli, char *chan)
{
	t_chan		*chans;

	if (!cli || !chan)
		return (-1);
	chans = cli->chans;
	while (chans)
	{
		if (ft_sec_strnccmp(chans->name, chan, CHAN_SIZE - 1) == SAME)
		{
			if (1 == 2)
				ft_printf(1, "=> %s IS into %s\n", cli->nick, chan);
			return (1);
		}
		chans = chans->next;
	}
	if (1 == 2)
		ft_printf(1, "=> %s IS NOT into %s\n", cli->nick, chan);
	return (0);
}

int			lst_client_is_user_in_channel(t_client *cnt, int sock, char *chan)
{
	t_client	*l;

	if (!cnt || !chan)
		return (-1);
	l = cnt;
	while (l)
	{
		if (sock == l->sock)
		{
			return (foreach_user_chans(l, chan));
		}
		l = l->next;
	}
	return (-1);
}
