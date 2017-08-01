/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_quit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 14:21:47 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 02:38:05 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static int		quit_all_chans(t_env *e, int sock)
{
	t_client	*node;
	t_chan		*chans;
	char		buf[MSG_SIZE];

	if (!(node = lst_client_get_node(e->cnt, sock)))
		return (-1);
	if (!(chans = node->chans))
		return (-1);
	while (chans)
	{
		ft_memset(buf, 0, MSG_SIZE);
		ft_strcat(buf, SRV_NAME);
		ft_strcat(buf, " QUIT :");
		ft_strcat(buf, chans->name);
		srv_speak_general(e, sock, buf);
		chans = chans->next;
	}
	return (0);
}

int				client_quit(t_env *e, int sock)
{
	char	*nick;

	if (!(nick = lst_client_get_nick(e->cnt, sock)))
		ft_printf(1, "[!] Cannot get nick\n");
	quit_all_chans(e, sock);
	ft_printf(1, "[%d] (%s) QUIT\n", sock, nick);
	lst_chan_del_by_name(&e->nicks, nick);
	del_sock_in_socks(e, sock);
	lst_client_del_node(&(e->cnt), sock);
	FD_CLR(sock, &e->fd_read);
	FD_CLR(sock, &e->fd_write);
	close(sock);
	if (e->dbg > 0)
		lst_client_put(e->cnt);
	return (0);
}
