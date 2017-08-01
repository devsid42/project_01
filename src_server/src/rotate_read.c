/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:43:12 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:52:25 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static int		reset_buf(t_client *node)
{
	node->start_rbuf = node->rbuf;
	node->stop_rbuf = node->rbuf;
	node->buflen = 0;
	ft_memset(node->rbuf, 0, RBUF_SIZE);
	return (0);
}

static void		handle_end_of_buf(t_env *e, t_client *node)
{
	size_t	len;

	if (node->buflen + RBUF_LIMIT >= RBUF_SIZE - 1)
	{
		if (node->start_rbuf != node->stop_rbuf)
		{
			len = ft_strlen(node->start_rbuf);
			ft_strncpy(node->rbuf, node->start_rbuf, len);
			node->buflen = len;
			node->start_rbuf = node->rbuf;
			node->stop_rbuf = node->rbuf + len;
			ft_memset(node->stop_rbuf, 0, RBUF_SIZE - node->buflen);
		}
		else
			reset_buf(node);
		if (e->dbg > 0)
			ft_printf(1, "[!] End of buffer, restart\n");
	}
}

static int		detect_spe_case(t_env *e, int sock, t_client *node, int len)
{
	if (*node->rbuf == 0 || len == 0)
		client_quit(e, sock);
	else if (len >= RBUF_LIMIT - 1)
	{
		ft_bprintf(sock, MSG_SIZE, "[!] Command too big\n");
		reset_buf(node);
	}
	else
		return (0);
	return (1);
}

static int		read_work(t_env *e, int sock, t_client *node)
{
	int		len;

	len = 0;
	handle_end_of_buf(e, node);
	if ((len = read(sock, node->stop_rbuf, RBUF_LIMIT)) == -1)
	{
		reset_buf(node);
		return (-1);
	}
	if (detect_spe_case(e, sock, node, len) == 1)
		return (0);
	node->buflen += len;
	node->stop_rbuf += len;
	if (e->dbg > 0)
		put_rotate_buf(node->rbuf, 20, node);
	if ((ft_strchr(node->start_rbuf, '\n')))
		return (1);
	if (e->dbg > 0)
		ft_printf(1, "%s[%d] No complet receive: [%s]%s\n",\
		GREEN, len, node->start_rbuf, RESET);
	return (0);
}

t_client		*rotate_read(t_env *e, int sock)
{
	t_client	*node;

	if (!(node = lst_client_get_node(e->cnt, sock)))
		return (NULL);
	if (read_work(e, sock, node) == 1)
		return (node);
	return (NULL);
}
