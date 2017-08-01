/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_quit_mode_ping.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:57:06 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:47:08 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static void	srv_mode_put(int sock, char *nick, char **cmds)
{
	ft_bprintf(sock, MSG_SIZE, ":%s 324 %s %s +nt\n", SRV_NAME, nick, cmds[1]);
	ft_bprintf(sock, MSG_SIZE, ":%s 329 %s %s 1494708558\n",\
			SRV_NAME, nick, cmds[1]);
}

int			srv_mode(t_env *e, int sock, char **cmds)
{
	char	*nick;

	nick = NULL;
	if (ft_sec_strnccmp(cmds[0], "MODE", 4) == 0)
	{
		if (!(nick = lst_client_get_nick(e->cnt, sock)))
			return (-1);
		if (!cmds[1] || *cmds[1] != '#')
		{
			ft_bprintf(sock, MSG_SIZE, ":%s 461 %s MODE :Not enough param\n",\
				SRV_NAME, nick);
			return (1);
		}
		if (!(nick = lst_client_get_nick(e->cnt, sock)))
			return (-1);
		if (!lst_chan_get_name(e->chans, cmds[1]))
		{
			ft_bprintf(sock, MSG_SIZE, STR_NO_CHAN, nick, cmds[1]);
			return (0);
		}
		srv_mode_put(sock, nick, cmds);
		srv_names(e, sock, cmds);
		return (1);
	}
	return (0);
}

int			srv_ping_pong(int sock, char *msg)
{
	if (msg && ft_strnccmp(msg, "PING :", 6) == 0)
	{
		msg[1] = 'O';
		ft_bprintf(sock, MSG_SIZE, "%s\n", msg);
		ft_printf(1, "%s\n", msg);
		return (1);
	}
	return (0);
}

int			srv_quit(t_env *e, int sock, char *buf)
{
	if (buf && ft_strnccmp(buf, "QUIT :", 6) == 0)
	{
		client_quit(e, sock);
		return (1);
	}
	return (0);
}
