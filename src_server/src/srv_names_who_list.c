/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_names_who_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 00:27:11 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:48:39 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

int			srv_names(t_env *e, int sock, char **cmds)
{
	char		*nick;

	nick = NULL;
	if (ft_sec_strnccmp(cmds[0], "NAMES", 5) == SAME)
	{
		if (!(nick = lst_client_get_nick(e->cnt, sock)))
			return (-1);
		if (!cmds[1] || *cmds[1] != '#')
		{
			ft_bprintf(sock, MSG_SIZE, ":%s %s :/NAMES #<channel>\n",\
				nick, SRV_NAME);
			return (1);
		}
		lst_put_client_chan_nicks(e, sock, cmds[1], nick);
		ft_bprintf(sock, MSG_SIZE, ":%s 366 %s * :End of /NAMES list.\n",\
			SRV_NAME, nick);
		return (1);
	}
	return (0);
}

int			srv_list(t_env *e, int sock, char **cmds)
{
	char		*nick;
	t_chan		*l;

	nick = NULL;
	if (ft_sec_strnccmp(cmds[0], "LIST", 4) == SAME)
	{
		if (!(nick = lst_client_get_nick(e->cnt, sock)))
			return (-1);
		ft_bprintf(sock, MSG_SIZE, ":%s 321 %s Channel :", SRV_NAME, nick);
		l = e->chans;
		while (l)
		{
			ft_bprintf(sock, MSG_SIZE, "%s ", l->name);
			l = l->next;
		}
		ft_bprintf(sock, MSG_SIZE, "\n:%s 323 %s :End of /LIST\n",\
			SRV_NAME, nick);
		return (1);
	}
	return (0);
}

static int	srv_who_algo(int sock, char *nick, char *chan, t_client *cnt)
{
	t_client	*cn;
	t_chan		*chans;

	cn = cnt;
	while (cn)
	{
		if (cn->chans)
		{
			chans = cn->chans;
			while (chans)
			{
				if (ft_sec_strnccmp(\
					chans->name, chan, CHAN_SIZE - 1) == SAME)
				{
					ft_bprintf(sock, MSG_SIZE, ":%s 352 %s * %s ",\
						SRV_NAME, nick, cn->user);
					ft_bprintf(sock, MSG_SIZE, "IPtruc SRV %s H :0 realname\n",\
						cn->nick);
				}
				chans = chans->next;
			}
		}
		cn = cn->next;
	}
	return (0);
}

int			srv_who(t_env *e, int sock, char **cmds)
{
	char		*nick;

	nick = NULL;
	if (ft_sec_strnccmp(cmds[0], "WHO", 3) == SAME)
	{
		if (!(nick = lst_client_get_nick(e->cnt, sock)))
			return (-1);
		if (!cmds[1] || *cmds[1] != '#')
		{
			ft_printf(sock, "%s Need a channel with (%s)\n",\
				SRV_NAME, cmds[1]);
			return (1);
		}
		srv_who_algo(sock, nick, cmds[1], e->cnt);
		ft_bprintf(sock, MSG_SIZE, ":%s 315 %s * :End of /WHO list.\n",\
			SRV_NAME, nick);
		return (1);
	}
	return (0);
}
