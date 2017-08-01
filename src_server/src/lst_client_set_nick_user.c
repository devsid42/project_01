/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_client_set_nick_user.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 19:01:12 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 00:44:22 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

int			lst_client_set_nick(t_client *cnt, int sock, char *nick)
{
	t_client	*l;

	if (!cnt)
		return (-1);
	l = cnt;
	while (l)
	{
		if (l->sock == sock)
		{
			ft_strncpy(l->nick, nick, NICK_SIZE - 1);
			return (1);
		}
		l = l->next;
	}
	ft_printf(1, "[!] Client not found in client_nick: %d\n", sock);
	return (0);
}

int			lst_client_set_user(t_client *cnt, int sock, char *user)
{
	t_client	*l;

	if (!cnt)
		return (-1);
	l = cnt;
	while (l)
	{
		if (l->sock == sock)
		{
			ft_strncpy(l->user, user, NICK_SIZE - 1);
			return (1);
		}
		l = l->next;
	}
	ft_printf(1, "[!] Client not found in client_user: %d\n", sock);
	return (0);
}
