/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_client_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 21:51:19 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 19:14:48 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

t_client	*lst_client_create(int sock, t_sockaddr_in *addr)
{
	t_client	*node;

	if (!(node = (t_client *)ft_memalloc(sizeof(t_client))))
		return (NULL);
	node->connected = 0;
	ft_memset(node->rbuf, 0, RBUF_SIZE);
	node->start_rbuf = node->rbuf;
	node->stop_rbuf = node->rbuf;
	node->buflen = 0;
	ft_memset(node->ip, 0, IP_BUF_SIZE);
	ft_memset(node->nick, 0, NICK_SIZE);
	ft_memset(node->user, 0, NICK_SIZE);
	node->chans = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->sock = sock;
	ft_strncpy(node->ip, inet_ntoa(addr->sin_addr), IP_BUF_SIZE - 1);
	node->port = ntohs(addr->sin_port);
	ft_printf(1, "New client Socket: %d\nIP: %s\nPort: %d\n",\
		node->sock, node->ip, node->port);
	return (node);
}
