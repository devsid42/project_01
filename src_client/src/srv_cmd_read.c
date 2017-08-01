/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_cmd_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 17:07:51 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:18:00 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

int		srv_user_nick(t_env *e, char *buf, char **cmds)
{
	if (ft_sec_strnccmp(cmds[1], "NICK", 4) == SAME)
	{
		if (!(buf = ft_strchr(buf, ':')))
			return (-1);
		buf += 1;
		ft_strncpy(e->nick, buf, NICK_SIZE - 1);
	}
	return (0);
}

int		srv_user_join(t_env *e, char *buf, char **cmds)
{
	char	*chan;

	chan = NULL;
	if (ft_sec_strnccmp(cmds[1], "JOIN", 4) == SAME)
	{
		if (!(chan = get_channel(buf)))
			return (-1);
		if (lst_chan_get_name(e->chans, chan))
			return (0);
		lst_chan_add_end(&e->chans, lst_chan_create(chan));
		e->cur_chan = lst_chan_get_last_name(e->chans);
		lst_chan_put(e->chans, "Chans ", 0);
		ft_strdel(&chan);
	}
	return (0);
}

int		srv_user_part(t_env *e, char *buf, char **cmds)
{
	char	*chan;

	chan = NULL;
	if (ft_sec_strnccmp(cmds[1], "PART", 4) == SAME)
	{
		if (!e->chans)
			return (0);
		if (!(chan = get_channel(buf)))
		{
			chan = lst_chan_get_last_name(e->chans);
			lst_chan_del_by_name(&e->chans, chan);
		}
		else
		{
			lst_chan_del_by_name(&e->chans, chan);
			ft_strdel(&chan);
		}
		e->cur_chan = lst_chan_get_last_name(e->chans);
		lst_chan_put(e->chans, "Chans ", 0);
	}
	return (0);
}

int		srv_ping_pong(int sock, char *msg)
{
	if (msg && ft_strnccmp(msg, "PING :", 6) == 0)
	{
		msg[1] = 'O';
		ft_bprintf(sock, MSG_SIZE, "%s\n", msg);
		ft_printf(1, "%s\n", msg);
	}
	else
		return (0);
	return (1);
}
