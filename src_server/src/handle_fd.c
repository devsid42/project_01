/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 22:45:46 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:54:48 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static int		handle_new_client(t_env *e)
{
	int			sock;
	t_client	*node;

	if ((sock = accept(\
		e->srv_sock, (t_sockaddr *)&(e->addr), &e->sock_len)) > -1)
	{
		FD_SET(sock, &e->fd_read);
		if (add_sock_in_socks(e, sock) == 0)
		{
			ft_printf(1, "[!] Too much users\n");
			ft_bprintf(sock, MSG_SIZE, ":%s :[!] Too much users\n", SRV_NAME);
			FD_CLR(sock, &e->fd_read);
			close(sock);
		}
		if (!(node = lst_client_create(sock, &(e->addr))))
		{
			ft_printf(1, "[!] Cannot create lst client");
			return (-1);
		}
		lst_client_add_end(&e->cnt, node);
	}
	else
		ft_printf(2, "[!] Error accept client\n");
	return (0);
}

static int		already_connected(t_env *e, int sock, char *buf, char **cmds)
{
	t_client	*node;

	if (!(node = lst_client_get_node(e->cnt, sock)))
		return (-1);
	if (node->connected == 0)
	{
		ft_bprintf(sock, MSG_SIZE, ":%s MODE %s :+i\n",\
			node->nick, node->nick);
		node->connected = 1;
	}
	srv_join_part(e, buf, cmds, sock);
	if (srv_speak_msg(e, sock, buf, cmds) == 1
		|| srv_who(e, sock, cmds) == 1
		|| srv_mode(e, sock, cmds) == 1
		|| srv_ping_pong(sock, buf) == 1
		|| srv_names(e, sock, cmds) == 1
		|| srv_list(e, sock, cmds) == 1
		|| srv_quit(e, sock, buf) == 1)
		return (1);
	srv_speak_general(e, sock, buf);
	return (0);
}

static int		handle_cmd(t_env *e, int sock, char *buf, char **cmds)
{
	t_client	*node;

	node = NULL;
	srv_user_nick(e, sock, cmds);
	if (lst_client_is_reg(e->cnt, sock) < 2)
	{
		if (ft_sec_strnccmp(cmds[0], "NICK", 4) != SAME
			&& ft_sec_strnccmp(cmds[0], "USER", 4) != SAME)
		{
			ft_bprintf(sock, MSG_SIZE, ":%s [!] Reg not complete\n", SRV_NAME);
			if (!(node = lst_client_get_node(e->cnt, sock)))
				return (-1);
			if (*node->nick == 0)
				ft_bprintf(sock, MSG_SIZE, ":%s (re)set NICK\n", SRV_NAME);
			else if (*node->user == 0)
				ft_bprintf(sock, MSG_SIZE, ":%s (re)set USER\n", SRV_NAME);
		}
	}
	else
		already_connected(e, sock, buf, cmds);
	return (0);
}

static int		handle_current_client(t_env *e, int sock)
{
	t_client	*node;
	char		**recv_cmds;
	char		**cmds;
	int			i;

	if (!(node = rotate_read(e, sock)))
		return (0);
	recv_cmds = ft_split(node->start_rbuf, "\r\n");
	node->start_rbuf = node->stop_rbuf;
	i = 0;
	while (recv_cmds && recv_cmds[i])
	{
		if ((cmds = ft_split(recv_cmds[i], " \t")))
		{
			ft_printf(1, "<[%s%s%s]\n", WHITE, recv_cmds[i], RESET);
			if (srv_is_known_cmd(sock, recv_cmds[i], cmds) > 0)
				handle_cmd(e, sock, recv_cmds[i], cmds);
			ft_freearray(cmds);
		}
		i += 1;
	}
	put_srv_info(e);
	ft_freearray(recv_cmds);
	return (0);
}

int				handle_fd(t_env *e)
{
	int			sock;

	sock = 3;
	while (sock < MAX_FD)
	{
		if (FD_ISSET(sock, &e->fd_read))
		{
			if (sock == e->srv_sock)
			{
				handle_new_client(e);
			}
			else
			{
				handle_current_client(e, sock);
			}
		}
		sock += 1;
	}
	return (0);
}
