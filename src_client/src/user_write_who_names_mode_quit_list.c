/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_write_who_names_mode_quit_list.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 17:25:05 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:15:31 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

int		user_write_who(t_env *e, char **cmds)
{
	if (ft_sec_strnccmp(cmds[0], "/WHO", 4) == SAME)
	{
		if (e->connected == 0)
		{
			ft_printf(1, "\r[*] Please connect first\n");
			return (1);
		}
		else if (!e->cur_chan)
		{
			ft_printf(1, "\r[*] Please join a channel first !\n");
			return (1);
		}
		else if (!cmds[1] || *cmds[1] != '#')
		{
			ft_printf(1, "\r[*] Need valid #channel\n");
			return (1);
		}
		ft_bprintf(e->sock, MSG_SIZE, "WHO %s\n", cmds[1]);
		return (1);
	}
	return (0);
}

int		user_write_mode(t_env *e, char **cmds)
{
	if (ft_sec_strnccmp(cmds[0], "/MODE", 5) == SAME)
	{
		if (e->connected == 0)
		{
			ft_printf(1, "\r[*] Please connect first\n");
			return (1);
		}
		else if (!cmds[1])
		{
			ft_printf(1, "\r[*] /MODE Need channel argument\n");
			return (1);
		}
		ft_bprintf(e->sock, MSG_SIZE, "MODE %s\n", cmds[1]);
		return (1);
	}
	return (0);
}

int		user_write_names(t_env *e, char **cmds)
{
	if (ft_sec_strnccmp(cmds[0], "/NAMES", 6) == SAME)
	{
		if (e->connected == 0)
		{
			ft_printf(1, "\r[*] Please connect first\n");
			return (1);
		}
		else if (!cmds[1] || *cmds[1] != '#')
		{
			ft_printf(1, "\r[*] Need valid #channel\n");
			ft_printf(1, "\r[*] Use /LIST for knowing all srv chans\n");
			return (1);
		}
		ft_bprintf(e->sock, MSG_SIZE, "NAMES %s\n", cmds[1]);
		return (1);
	}
	return (0);
}

int		user_write_list(t_env *e, char **cmds)
{
	if (ft_sec_strnccmp(cmds[0], "/LIST", 5) == SAME)
	{
		if (e->connected == 0)
		{
			ft_printf(1, "\r[*] Please connect first\n");
			return (1);
		}
		ft_bprintf(e->sock, MSG_SIZE, "LIST\n");
		return (1);
	}
	return (0);
}

int		user_write_quit(t_env *e, char **cmds)
{
	if (ft_sec_strnccmp(cmds[0], "/QUIT", 5) == SAME
		|| ft_sec_strnccmp(cmds[0], "/Q", 2) == SAME)
	{
		if (e->connected == 1)
		{
			ft_bprintf(e->sock, MSG_SIZE, "QUIT :Bye! (%s)\n", e->nick);
			close(e->sock);
		}
		exit(0);
	}
	return (0);
}
