/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 22:52:49 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/01 23:17:55 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

void	init_fd(t_env *e)
{
	if (!e)
		return ;
	FD_ZERO(&e->fd_read);
	FD_SET(0, &e->fd_read);
	FD_SET(e->sock, &e->fd_read);
	FD_SET(e->sock, &e->fd_write);
}

int		init_env(t_env *e)
{
	e->connected = 0;
	e->ip = NULL;
	e->chans = NULL;
	e->cur_chan = NULL;
	ft_strncpy(e->nick, NICK, NICK_SIZE - 1);
	ft_strncpy(e->user, USER, NICK_SIZE - 1);
	e->tv.tv_sec = 5;
	e->tv.tv_usec = 0;
	ft_memset(&e->fd_read, 0, sizeof(fd_set));
	ft_memset(&e->fd_write, 0, sizeof(fd_set));
	return (0);
}

int		run_client(t_env *e, int choice)
{
	if (!e)
		return (-1);
	if (choice == 3 || choice == 5)
	{
		if (init_stream_client(e) == -1)
			return (-1);
		send_credential(e->sock, e->nick, e->user);
		e->connected = 1;
	}
	put_prompt(e);
	while (42)
	{
		init_fd(e);
		if (select(e->sock + 1, &e->fd_read, &e->fd_write, NULL, NULL) < 1)
			ft_printf(1, "\rError select\n");
		else
		{
			if (FD_ISSET(0, &e->fd_read))
				client_write(e);
			else if (FD_ISSET(e->sock, &e->fd_read))
				client_read(e);
		}
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_env	e;

	if (1 == 2)
		init_window();
	ft_memset(&e, 0, sizeof(t_env));
	init_env(&e);
	signal(SIGINT, &handle_ctrl_c);
	if (argc == 1)
		run_client(&e, argc);
	else if (argc == 2 && ft_strncmp(argv[1], "-h", 2) == 0)
		ft_printf(1, USAGE, argv[0]);
	else if (argc == 3 || argc == 5)
	{
		e.ip = ft_strdup(argv[1]);
		e.port = ft_atoi(argv[2]);
		if (argc == 5)
		{
			ft_strncpy(e.nick, argv[3], NICK_SIZE - 1);
			ft_strncpy(e.user, argv[4], NICK_SIZE - 1);
		}
		run_client(&e, argc);
	}
	else
		ft_printf(1, USAGE, argv[0]);
	return (0);
}
