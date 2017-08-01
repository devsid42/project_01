/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_del_sock_in_socks.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 18:47:59 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/29 21:02:16 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

int		add_sock_in_socks(t_env *e, int sock)
{
	int		i;

	i = 0;
	while (i < MAX_FD)
	{
		if (e->socks[i] == -1)
		{
			e->socks[i] = sock;
			if (e->dbg > 0)
				ft_printf(1, "[*] ADD SOCK %d at [%d]\n", sock, i);
			return (1);
		}
		i += 1;
	}
	return (0);
}

int		del_sock_in_socks(t_env *e, int sock)
{
	int		i;

	i = 0;
	while (i < MAX_FD)
	{
		if (e->socks[i] == sock)
		{
			e->socks[i] = -1;
			if (e->dbg > 0)
				ft_printf(1, "[*] DEL SOCK %d at [%d]\n", sock, i);
			return (1);
		}
		i += 1;
	}
	ft_printf(2, "[!] Cannot remove sock\n");
	return (0);
}
