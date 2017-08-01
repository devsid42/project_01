/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_write_join_part.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:15:50 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:17:18 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

int				user_write_join(t_env *e, char **cmds)
{
	if (!cmds[0])
		return (-1);
	if (ft_sec_strnccmp(cmds[0], "/JOIN", 5) == SAME && cmds[1])
	{
		if (e->connected == 0)
			ft_printf(1, "\r[*] Please connect first\n");
		else if (lst_chan_get_name(e->chans, cmds[1]))
			ft_printf(1, "\r[*] Already in this channel\n");
		else
			ft_bprintf(e->sock, MSG_SIZE, "JOIN %s\n", cmds[1]);
		return (1);
	}
	return (0);
}

static int		user_write_part_more(t_env *e, char *buf)
{
	char	*chan;

	chan = NULL;
	if (!(chan = get_channel(buf)))
	{
		ft_printf(1, "\r[!] Bad channel format\n");
		return (-1);
	}
	ft_bprintf(e->sock, MSG_SIZE, "PART %s\n", chan);
	lst_chan_del_by_name(&e->chans, chan);
	e->cur_chan = lst_chan_get_last_name(e->chans);
	ft_strdel(&chan);
	return (0);
}

int				user_write_part(t_env *e, char *buf, char **cmds)
{
	if (!cmds[0])
		return (-1);
	if (ft_sec_strnccmp(cmds[0], "/LEAVE", 6) == SAME)
	{
		if (e->connected == 0)
			ft_printf(1, "\r[*] Please connect first\n");
		else if (!lst_chan_get_last_name(e->chans))
			ft_printf(1, "\r[*] Please join a channel first\n");
		else if (!cmds[1])
		{
			ft_bprintf(e->sock, MSG_SIZE, "PART %s\n", e->cur_chan);
			lst_chan_del_by_name(&e->chans, e->cur_chan);
			e->cur_chan = lst_chan_get_last_name(e->chans);
		}
		else
		{
			user_write_part_more(e, buf);
		}
		lst_chan_put(e->chans, "Chans ", 0);
		return (1);
	}
	return (0);
}
