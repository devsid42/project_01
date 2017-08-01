/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_write_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:12:17 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 00:10:28 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

int		user_write_help(char **cmds)
{
	if (ft_sec_strnccmp(cmds[0], "/HELP", 5) == SAME)
	{
		ft_printf(1, "****************************************************\n");
		ft_printf(1, "**               HELP COMMANDS                    **\n");
		ft_printf(1, "****************************************************\n");
		ft_printf(1, "* /HELP\n");
		ft_printf(1, "* /CONNECT <ip> [port]\n");
		ft_printf(1, "* /NICK <nick>\n");
		ft_printf(1, "* /USER <user>\n");
		ft_printf(1, "* /JOIN <#channel>\n");
		ft_printf(1, "* /LEAVE [#channel]\n");
		ft_printf(1, "* /WHO <#channel>\n");
		ft_printf(1, "* /NAMES [#channel]\n");
		ft_printf(1, "* /CHAN [#channel]\n");
		ft_printf(1, "* /MODE <#channel>\n");
		ft_printf(1, "* /LIST\n");
		ft_printf(1, "* /QUIT\n");
		return (1);
	}
	return (0);
}
