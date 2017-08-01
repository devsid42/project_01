/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_write_connect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:25:43 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 19:23:25 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

int		user_write_connect(t_env *e, char **cmds)
{
	if (ft_sec_strnccmp(cmds[0], "/CONNECT", 8) == 0 && cmds[1])
	{
		ft_strdel(&e->ip);
		e->cur_chan = NULL;
		lst_chan_delete_all(&e->chans);
		close(e->sock);
		e->connected = 0;
		e->port = PORT;
		if (cmds[2])
			e->port = ft_atoi(cmds[2]);
		if (init_stream_client(e) != -1)
		{
			send_credential(e->sock, e->nick, e->user);
			e->connected = 1;
		}
		return (1);
	}
	return (0);
}
