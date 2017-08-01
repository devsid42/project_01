/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 17:36:25 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:20:32 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

static int	catch_builtin(t_env *e, char *buf, char **cmds)
{
	int		res;

	res = user_write_nick(e, cmds);
	res += user_write_user(e, cmds);
	res += user_write_join(e, cmds);
	res += user_write_part(e, buf, cmds);
	res += user_write_msg(e, cmds, buf);
	res += user_write_connect(e, cmds);
	res += user_write_chan(e, cmds);
	res += user_write_who(e, cmds);
	res += user_write_names(e, cmds);
	res += user_write_list(e, cmds);
	res += user_write_mode(e, cmds);
	res += user_write_quit(e, cmds);
	res += user_write_help(cmds);
	return (res);
}

static int	catch_stdin(t_env *e, char *buf, char **cmds)
{
	char	*ptr;

	ptr = buf;
	if (*cmds[0] != '/' && *buf != 0)
	{
		if (lst_chan_get_last_name(e->chans))
			ft_bprintf(e->sock, MSG_SIZE, "PRIVMSG %s :%s\n", e->cur_chan, buf);
		else
			ft_printf(1, "[*] Please join a channel first\n");
	}
	else if (catch_builtin(e, buf, cmds) > 0)
	{
		if (1 == 2)
			ft_printf(1, "[*] Builtin cmd: %s\n", buf);
	}
	else if (*buf == '/')
	{
		if (1 == 2)
			ft_printf(1, "[*] Custom cmd\n");
		ft_bprintf(e->sock, MSG_SIZE, "%s\n", ++ptr);
	}
	return (0);
}

int			client_write(t_env *e)
{
	char	*buf;
	char	**cmds;

	if (get_next_line(0, &buf) < 0 || !buf || *buf == 0)
	{
		put_prompt(e);
		ft_strdel(&buf);
		return (0);
	}
	if (!(cmds = ft_split(buf, " \t\r")) || !cmds[0])
		return (-1);
	catch_stdin(e, buf, cmds);
	put_prompt(e);
	ft_strdel(&buf);
	ft_freearray(cmds);
	return (0);
}
