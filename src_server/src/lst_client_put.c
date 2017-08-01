/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_client_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 01:00:30 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:53:19 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

void			lst_client_put(t_client *cnt)
{
	t_client	*l;

	if (!cnt)
		return ;
	l = cnt;
	while (l)
	{
		FTPS(WHITE);
		FTPS("--\n");
		ft_printf(1, "Connected: %d\n", l->connected);
		ft_printf(1, "Sock: %d\n", l->sock);
		ft_printf(1, "IP  : %s\n", l->ip);
		ft_printf(1, "Port: %d/0x%x\n", l->port, (unsigned char)l->port);
		ft_printf(1, "Nick: %s\n", l->nick);
		ft_printf(1, "User: %s\n", l->user);
		lst_chan_put(l->chans, "Priv Chans ", 0);
		FTPS("--\n");
		FTPS(RESET);
		l = l->next;
	}
}

static int		put_user_from_chan(t_env *e, int sock, char *chan)
{
	t_client	*cl;
	t_chan		*ch;

	if (!e->cnt)
		return (-1);
	cl = e->cnt;
	while (cl)
	{
		if (cl->chans)
		{
			ch = cl->chans;
			while (ch)
			{
				if (chan
					&& ft_sec_strnccmp(ch->name, chan, CHAN_SIZE - 1) == SAME)
				{
					ft_bprintf(sock, MSG_SIZE, "%s ", cl->nick);
				}
				ch = ch->next;
			}
		}
		cl = cl->next;
	}
	ft_bprintf(sock, MSG_SIZE, "\n");
	return (0);
}

int				lst_put_client_chan_nicks(\
								t_env *e, int sock, char *chan, char *nick)
{
	t_chan		*ch;

	if (!e->chans)
	{
		ft_bprintf(sock, MSG_SIZE, ":%s Currently no chans opened\n", SRV_NAME);
		return (0);
	}
	ch = e->chans;
	while (ch)
	{
		if (chan && ft_sec_strnccmp(ch->name, chan, CHAN_SIZE - 1) == SAME)
		{
			ft_bprintf(sock, MSG_SIZE, ":%s 353 %s = %s :",\
				SRV_NAME, nick, ch->name);
			put_user_from_chan(e, sock, chan);
			return (1);
		}
		ch = ch->next;
	}
	return (0);
}
