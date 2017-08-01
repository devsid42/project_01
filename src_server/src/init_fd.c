/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 18:23:01 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/25 00:23:35 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

int		init_fd(t_env *e)
{
	int		i;

	i = 0;
	FD_ZERO(&e->fd_read);
	FD_SET(e->srv_sock, &e->fd_read);
	while (i < MAX_FD)
	{
		if (e->socks[i] != -1)
		{
			FD_SET(e->socks[i], &e->fd_read);
			FD_SET(e->socks[i], &e->fd_write);
		}
		i += 1;
	}
	return (0);
}
