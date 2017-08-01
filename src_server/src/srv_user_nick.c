/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_user_nick.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:38:05 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:45:01 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static int	srv_set_nick(t_env *e, int sock, char **cmds)
{
	t_chan	*node;

	if (lst_chan_get_name(e->nicks, cmds[1]))
		ft_bprintf(sock, MSG_SIZE, ":%s Please choose an other nick\n", SRV_NAME);
	else if (lst_client_get_nick(e->cnt, sock)
		&& !lst_client_get_user(e->cnt, sock))
	{
		ft_bprintf(sock, MSG_SIZE, ":%s Valid credential before\n", SRV_NAME);
	}
	else if (lst_client_get_nick(e->cnt, sock))
	{
		lst_client_set_nick(e->cnt, sock, cmds[1]);
		ft_bprintf(sock, MSG_SIZE, ":%s Nick updated\n", SRV_NAME);
	}
	else
	{
		lst_client_set_nick(e->cnt, sock, cmds[1]);
		if (!(node = lst_chan_create(cmds[1])))
			ft_printf(1, ":%s Cannot add nick\n", SRV_NAME);
		else
			lst_chan_add_end(&e->nicks, node);
	}
	return (0);
}

int			srv_user_nick(t_env *e, int sock, char **cmds)
{
	if (ft_sec_strnccmp(cmds[0], "USER", 4) == SAME && cmds[1])
		lst_client_set_user(e->cnt, sock, cmds[1]);
	else if (ft_sec_strnccmp(cmds[0], "NICK", 4) == SAME && cmds[1])
		srv_set_nick(e, sock, cmds);
	else
		return (0);
	return (1);
}
