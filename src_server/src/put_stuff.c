/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 13:07:30 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 00:12:52 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static void		put_rotate_zero(t_client *node, size_t i)
{
	if ((t_uchar)node->rbuf[i] <= 0xf
		&& &(node->rbuf[i]) == node->start_rbuf)
		ft_printf(1, "%s0%s", GREEN, RESET);
	else if ((t_uchar)node->rbuf[i] <= 0xf
		&& &(node->rbuf[i]) == node->stop_rbuf)
		ft_printf(1, "%s0%s", BLUE, RESET);
	else if ((t_uchar)node->rbuf[i] <= 0xf
		&& &(node->rbuf[i]) == node->start_rbuf + RBUF_LIMIT)
		ft_printf(1, "%s0%s", RED, RESET);
	else if ((t_uchar)node->rbuf[i] <= 0xf)
		ft_putchar('0');
}

void			put_rotate_buf(void *addr, size_t col, t_client *node)
{
	int		i;

	ft_printf(1, "%s=> BUF / %sSTART / %sSTOP <=%s\n",\
		GREEN, BLUE, RED, RESET);
	i = 0;
	while (i < RBUF_SIZE)
	{
		if (i > 0 && i % col == 0)
			ft_putchar('\n');
		if (i % col == 0)
			ft_printf(1, "[0x%p] ", addr + i);
		put_rotate_zero(node, i);
		if (&(node->rbuf[i]) == node->start_rbuf)
			ft_printf(1, "%s%x%s ", GREEN, (t_uchar)node->rbuf[i], RESET);
		else if (&(node->rbuf[i]) == node->stop_rbuf)
			ft_printf(1, "%s%x%s ", BLUE, (t_uchar)node->rbuf[i], RESET);
		else if (&(node->rbuf[i]) == node->start_rbuf + RBUF_LIMIT)
			ft_printf(1, "%s%x%s ", RED, (t_uchar)node->rbuf[i], RESET);
		else
			ft_printf(1, "%x ", (t_uchar)node->rbuf[i]);
		i += 1;
	}
	ft_putchar('\n');
}

void			put_srv_info(t_env *e)
{
	if (e->dbg > 0)
	{
		lst_client_put(e->cnt);
		lst_chan_put(e->nicks, "All Nicks :", 0);
		lst_chan_put(e->chans, "All Chans :", 0);
	}
}
