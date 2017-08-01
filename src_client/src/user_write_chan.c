/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_write_chan.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:12:17 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 00:15:29 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

int		user_write_chan(t_env *e, char **cmds)
{
	if (ft_sec_strnccmp(cmds[0], "/CHAN", 5) == 0)
	{
		if (cmds[1])
		{
			if (e->connected == 0)
			{
				ft_printf(1, "\r[*] Please connect first\n");
				return (1);
			}
			if (!(e->cur_chan = lst_chan_get_name(e->chans, cmds[1])))
			{
				ft_printf(1, "\r[*] Join channel before\n");
				e->cur_chan = lst_chan_get_last_name(e->chans);
			}
		}
		lst_chan_put(e->chans, "Chans ", 0);
		return (1);
	}
	return (0);
}
