/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_speak.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:35:25 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:46:07 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

int			srv_speak_msg(t_env *e, int src_sock, char *buf, char **cmds)
{
	char		*src_nick;
	int			dst_sock;

	src_nick = NULL;
	if (!buf || !cmds || ft_arraylen(cmds) < 3)
		return (-1);
	if (ft_sec_strnccmp(cmds[0], "PRIVMSG", 7) != SAME)
		return (0);
	if (*cmds[1] == '#')
		return (0);
	if (*cmds[2] != ':')
		return (-1);
	if (!(src_nick = lst_client_get_nick(e->cnt, src_sock)))
		return (-1);
	if (!(buf = ft_strchr(buf, ':')))
		return (-1);
	if ((dst_sock = lst_client_get_sock(e->cnt, cmds[1])) == -1)
		return (-1);
	ft_bprintf(dst_sock, MSG_SIZE, ":%s PRIVMSG %s %s\n",\
		src_nick, cmds[1], buf);
	return (1);
}

static int	recv_server(char *nick, char *buf, int *i)
{
	if (*i == 0)
		ft_printf(1, ">[%s:%s %s%s]\n", WHITE, nick, buf, RESET);
	return (0);
}

static int	privmsg_info(int nb_user, char *buf, char *chan)
{
	if (ft_strstr(buf, "PRIVMSG"))
		ft_printf(1, "[*] SENT to %d user(s) in [%s]\n", nb_user, chan);
	return (0);
}

static int	put_general(t_env *e, char *buf, char *nick, int *i)
{
	ft_bprintf(e->socks[*i], MSG_SIZE, ":%s %s\n", nick, buf);
	return (1);
}

int			srv_speak_general(t_env *e, int src_sock, char *buf)
{
	int		i;
	int		nb_user;
	char	*chan;
	char	*nick;

	nb_user = 0;
	nick = lst_client_get_nick(e->cnt, src_sock);
	chan = get_channel(buf);
	i = 0;
	while (i < MAX_FD)
	{
		recv_server(nick, buf, &i);
		if (e->socks[i] != -1)
		{
			if (lst_client_is_reg(e->cnt, e->socks[i]) == 2
			&& e->socks[i] != src_sock
			&& lst_client_is_user_in_channel(e->cnt, e->socks[i], chan) == 1)
				nb_user += put_general(e, buf, nick, &i);
		}
		i += 1;
	}
	privmsg_info(nb_user, buf, chan);
	ft_strdel(&chan);
	return (0);
}
