/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_write_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:25:33 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:16:52 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

static int		error_case(t_env *e)
{
	if (e->connected == 0)
		ft_printf(1, "\r[*] Please connect first\n");
	else
		return (0);
	return (1);
}

int				user_write_msg(t_env *e, char **cmds, char *buf)
{
	char	**msgs;
	int		i;

	if (ft_sec_strnccmp(cmds[0], "/MSG", 4) == SAME && cmds[1] && cmds[2])
	{
		if (error_case(e) == 1)
			return (1);
		if (!(msgs = ft_split(buf, " \t\r")))
			return (0);
		ft_bprintf(e->sock, MSG_SIZE, "PRIVMSG %s :", msgs[1]);
		i = 2;
		while (msgs[i])
			ft_bprintf(e->sock, MSG_SIZE, "%s ", msgs[i++]); //concat
		ft_bprintf(e->sock, MSG_SIZE, "\n");
		ft_freearray(msgs);
		return (1);
	}
	return (0);
}
