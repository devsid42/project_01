/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_join_part.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 01:53:49 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:50:45 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static int		srv_join(t_env *e, char **cmds, int sock, char *chan)
{
	t_client	*node;
	char		*nick;

	nick = NULL;
	node = NULL;
	if (ft_sec_strnccmp(cmds[0], "JOIN", 4) == SAME)
	{
		if (!(nick = lst_client_get_nick(e->cnt, sock)))
			return (-1);
		ft_bprintf(sock, MSG_SIZE, ":%s JOIN %s\n", nick, chan);
		if (!lst_chan_get_name(e->chans, chan))
			lst_chan_add_end(&e->chans, lst_chan_create(chan));
		if (!(node = lst_client_get_node(e->cnt, sock)))
			return (-1);
		if (!lst_chan_get_name(node->chans, chan))
			lst_chan_add_end(&node->chans, lst_chan_create(chan));
		lst_put_client_chan_nicks(e, sock, cmds[1], nick);
		ft_bprintf(sock, MSG_SIZE, ":%s 366 %s %s :End of /NAMES list.\n",\
			SRV_NAME, nick, cmds[1]);
		return (1);
	}
	return (0);
}

static int		srv_part(t_env *e, char **cmds, int sock, char *chan)
{
	t_client	*node;
	char		*nick;

	node = NULL;
	nick = NULL;
	if (ft_sec_strnccmp(cmds[0], "PART", 4) == SAME)
	{
		if (lst_chan_get_name(e->chans, chan)
			&& lst_client_channel_user_nb(e->cnt, chan) < 2)
			lst_chan_del_by_name(&e->chans, chan);
		if (!(node = lst_client_get_node(e->cnt, sock)))
			return (-1);
		if (lst_chan_get_name(node->chans, chan))
			lst_chan_del_by_name(&node->chans, chan);
		if (!(nick = lst_client_get_nick(e->cnt, sock)))
			return (-1);
		ft_bprintf(sock, MSG_SIZE, ":%s PART %s\n", nick, chan);
		return (1);
	}
	return (0);
}

int				srv_join_part(t_env *e, char *buf, char **cmds, int sock)
{
	char		*chan;
	int			res;

	if (!buf || !cmds)
		return (-1);
	if (ft_sec_strnccmp(cmds[0], "JOIN", 4) != SAME
		&& ft_sec_strnccmp(cmds[0], "PART", 4) != SAME)
		return (0);
	if (!(chan = get_channel(buf)))
		return (-1);
	res = srv_join(e, cmds, sock, chan);
	res += srv_part(e, cmds, sock, chan);
	if (res == 0)
		ft_bprintf(sock, MSG_SIZE, ":[!] %s Bad syntax\n", SRV_NAME);
	ft_strdel(&chan);
	return (res);
}
