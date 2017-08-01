/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_client_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 21:18:34 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/27 17:29:57 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

char		*lst_client_get_user(t_client *cnt, int sock)
{
	t_client	*l;

	if (!cnt)
		return (NULL);
	l = cnt;
	while (l)
	{
		if (l->sock == sock)
		{
			if (*l->user)
				return (l->user);
			else
				return (NULL);
		}
		l = l->next;
	}
	return (NULL);
}

char		*lst_client_get_nick(t_client *cnt, int sock)
{
	t_client	*l;

	if (!cnt)
		return (NULL);
	l = cnt;
	while (l)
	{
		if (l->sock == sock)
		{
			if (*l->nick)
				return (l->nick);
			else
				return (NULL);
		}
		l = l->next;
	}
	return (NULL);
}

t_client	*lst_client_get_node(t_client *cnt, int sock)
{
	t_client	*l;

	if (!cnt)
		return (NULL);
	l = cnt;
	while (l)
	{
		if (l->sock == sock)
			return (l);
		l = l->next;
	}
	return (NULL);
}

char		*lst_client_get_rbuf(t_client *cnt, int sock)
{
	t_client	*l;

	if (!cnt)
		return (NULL);
	l = cnt;
	while (l)
	{
		if (l->sock == sock)
			return (l->rbuf);
		l = l->next;
	}
	return (NULL);
}

int			lst_client_get_sock(t_client *cnt, char *nick)
{
	t_client	*l;

	if (!cnt)
		return (-1);
	l = cnt;
	while (l)
	{
		if (ft_sec_strnccmp(l->nick, nick, NICK_SIZE - 1) == 0)
			return (l->sock);
		l = l->next;
	}
	return (-1);
}
