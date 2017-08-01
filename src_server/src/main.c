/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 22:41:06 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 19:01:43 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

int		init_struct(t_env *e)
{
	if (RBUF_SIZE < 256 || RBUF_SIZE < RBUF_LIMIT * BUF_COEF)
	{
		ft_printf(2, "[!] Set a bigger/better RBUF_SIZE and/or COEF\n");
		return (-1);
	}
	ft_memset(&e->sin, 0, sizeof(t_sockaddr_in));
	ft_memset(&e->addr, 0, sizeof(t_sockaddr));
	e->sock_len = sizeof(t_sockaddr_in);
	e->socks = NULL;
	e->chans = NULL;
	e->nicks = NULL;
	e->cnt = NULL;
	if (!(e->socks = (int *)malloc(sizeof(int) * MAX_FD)))
		return (-1);
	ft_memset(e->socks, -1, sizeof(int) * MAX_FD);
	e->tv.tv_sec = 5;
	e->tv.tv_usec = 0;
	ft_memset(&e->fd_read, 0, sizeof(fd_set));
	ft_memset(&e->fd_write, 0, sizeof(fd_set));
	e->dbg = 0;
	return (0);
}

int		run_server(t_env *e)
{
	if (!e || init_stream_server(e) == -1)
		return (-1);
	ft_printf(1, "[*] Server sock: %d\n", e->srv_sock);
	while (42)
	{
		init_fd(e);
		if (select(MAX_FD, &e->fd_read, &e->fd_write, NULL, NULL) == -1)
			ft_printf(1, "Error select\n");
		handle_fd(e);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_env		e;

	if (argc < 2)
		ft_printf(1, "Usage: %s [-v] <port>\n", argv[0]);
	else
	{
		handle_signal();
		ft_memset(&e, 0, sizeof(t_env));
		if (init_struct(&e) == -1)
			return (-1);
		if (argc == 2)
			e.srv_port = ft_atoi(argv[1]);
		else if (argc == 3
			&& ft_sec_strnccmp(argv[1], "-v", 2) == SAME)
		{
			ft_printf(1, "[*] Verbose mode\n");
			e.dbg = 1;
			e.srv_port = ft_atoi(argv[2]);
		}
		if (run_server(&e) == -1)
			return (-1);
		close(e.srv_sock);
		free(e.socks);
	}
	return (0);
}
