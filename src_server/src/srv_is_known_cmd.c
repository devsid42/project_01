/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_is_known_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 02:02:35 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:51:57 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static int	k_nick_user(int sock, char **cmds)
{
	size_t	i;

	i = 0;
	if (!cmds[1])
		return (0);
	if (ft_strlen(cmds[1]) > 9)
	{
		ft_bprintf(sock, MSG_SIZE, ":%s len(nick) > 9\n", SRV_NAME);
		return (0);
	}
	while (cmds[1][i])
	{
		if (!ft_isalnum(cmds[1][i]) && cmds[1][i] != '_')
		{
			ft_bprintf(sock, MSG_SIZE, ":%s nick/user [a-z0-9_]\n", SRV_NAME);
			return (0);
		}
		i += 1;
	}
	return (1);
}

static int	k_join_part(int sock, char **cmds)
{
	if (!cmds[1] || *cmds[1] != '#' || ft_strlen(cmds[1]) < 2)
	{
		ft_bprintf(sock, MSG_SIZE, ":%s chan #[a-z0-9_]\n", SRV_NAME);
		return (0);
	}
	return (1);
}

static int	k_privmsg(int sock, char *buf, char **cmds)
{
	if (ft_arraylen(cmds) < 3)
	{
		ft_bprintf(sock, MSG_SIZE, ":%s PRIVMSG need more args\n", SRV_NAME);
		return (0);
	}
	else if (!ft_strchr(buf, ':'))
	{
		ft_bprintf(sock, MSG_SIZE, ":%s Bad cmd RFC syntax !\n", SRV_NAME);
		return (0);
	}
	return (1);
}

static int	srv_is_known_cmd_suite(char **cmds)
{
	if (ft_sec_strnccmp(cmds[0], "ERROR", 5) == SAME)
		return (1);
	else if (ft_sec_strnccmp(cmds[0], "NAMES", 5) == SAME)
		return (1);
	else if (ft_sec_strnccmp(cmds[0], "QUIT", 4) == SAME)
		return (1);
	else if (ft_sec_strnccmp(cmds[0], "HELP", 4) == SAME)
		return (1);
	else if (ft_sec_strnccmp(cmds[0], "LIST", 4) == SAME)
		return (1);
	return (0);
}

int			srv_is_known_cmd(int sock, char *buf, char **cmds)
{
	if (!cmds || !cmds[0])
		return (-1);
	if (ft_sec_strnccmp(cmds[0], "NICK", 4) == SAME
		|| ft_sec_strnccmp(cmds[0], "USER", 4) == SAME)
		return (k_nick_user(sock, cmds));
	else if (ft_sec_strnccmp(cmds[0], "JOIN", 4) == SAME
		|| ft_sec_strnccmp(cmds[0], "PART", 4) == SAME)
		return (k_join_part(sock, cmds));
	else if (ft_sec_strnccmp(cmds[0], "WHO", 3) == SAME)
		return (1);
	else if (ft_sec_strnccmp(cmds[0], "PRIVMSG", 7) == SAME)
		return (k_privmsg(sock, buf, cmds));
	else if (ft_sec_strnccmp(cmds[0], "MODE", 4) == SAME)
		return (1);
	else if (ft_sec_strnccmp(cmds[0], "PING", 4) == SAME
		|| ft_sec_strnccmp(cmds[0], "PONG", 4) == SAME)
		return (1);
	if (srv_is_known_cmd_suite(cmds) == 1)
		return (1);
	ft_bprintf(sock, MSG_SIZE, ":%s ERROR :Unknown command\n", SRV_NAME);
	return (0);
}
