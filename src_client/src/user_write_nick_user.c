/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_write_nick_user.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 18:11:11 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:15:49 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

int		user_write_nick(t_env *e, char **cmds)
{
	if (ft_sec_strnccmp(cmds[0], "/NICK", 5) == SAME && cmds[1])
	{
		if (ft_strlen(cmds[1]) > 9)
			ft_printf(1, "[!] nick > 9\n");
		else
		{
			ft_strncpy(e->nick, cmds[1], NICK_SIZE - 1);
			ft_bprintf(e->sock, MSG_SIZE, "NICK %s\n", cmds[1]);
		}
		return (1);
	}
	return (0);
}

int		user_write_user(t_env *e, char **cmds)
{
	if (ft_sec_strnccmp(cmds[0], "/USER", 5) == SAME && cmds[1])
	{
		if (ft_strlen(cmds[1]) > 9)
			ft_printf(1, "[!] user > 9\n");
		else
		{
			ft_strncpy(e->user, cmds[1], NICK_SIZE - 1);
			ft_bprintf(e->sock, MSG_SIZE, "USER %s %s_ %s %s\n",\
				cmds[1], cmds[1], cmds[1], cmds[1]);
		}
		return (1);
	}
	return (0);
}
