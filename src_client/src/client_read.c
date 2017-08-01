/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 17:07:51 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 13:01:59 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

static int		catch_cmd(t_env *e, char *buf, char **cmds)
{
	char	*ptr;

	if (!buf || !cmds)
		return (-1);
	ptr = buf;
	ptr += 1;
	srv_ping_pong(e->sock, buf);
	if (*buf != ':' || *e->nick == 0
		|| ft_strnccmp(ptr, e->nick, ft_strlen(e->nick)) != SAME)
		return (0);
	srv_user_nick(e, buf, cmds);
	srv_user_join(e, buf, cmds);
	srv_user_part(e, buf, cmds);
	return (0);
}

static int		put_privmsg(t_env *e, char *buf, char **cmds)
{
	char	*ptr;

	ptr = NULL;
	if (ft_sec_strnccmp(cmds[1], "PRIVMSG", 7) == SAME
		&& ft_strocc(buf, ':') == 2)
	{
		if (!(ptr = ft_strchr(buf + 1, ':')))
			return (-1);
		*ptr = 0;
		if (ft_strlen(buf) < ft_strlen(e->cur_chan) +\
			ft_strlen(e->nick) + ft_strlen(e->user) + ft_strlen("[](/)$>"))
		{
			ft_printf(1, "\r%s", buf);
		}
		else
		{
			ft_printf(1, "\r%s", buf);
		}
		ft_putchar(':');
		ptr += 1;
		ft_printf(1, "%s%s%s                           \n", WHITE, ptr, RESET);
		return (1);
	}
	return (0);
}

int				client_read(t_env *e)
{
	char	*buf;
	char	**cmds;

	if (!e)
		return (-1);
	get_next_line(e->sock, &buf);
	get_server_status(buf);
	if (!(cmds = ft_split(buf, " \t\r\n")))
		return (-1);
	if (put_privmsg(e, buf, cmds) != 1)
	{
		if (ft_strlen(buf) < ft_strlen(e->cur_chan) +\
			ft_strlen(e->nick) + ft_strlen(e->user) + ft_strlen("[](/)$>"))
		{
			ft_printf(1, "\r%s                                       \n", buf);
		}
		else
		{
			ft_printf(1, "\r%s\n", buf);
		}
	}
	catch_cmd(e, buf, cmds);
	put_prompt(e);
	ft_strdel(&buf);
	ft_freearray(cmds);
	return (0);
}
