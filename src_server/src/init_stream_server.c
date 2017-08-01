/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stream_server.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 17:07:51 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/29 15:19:04 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static int				get_socket_stream(void)
{
	int		sock;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ft_printf(2, "[!] Can't create socket stream\n");
	return (sock);
}

static t_sockaddr_in	get_sockaddr(short port)
{
	t_sockaddr_in	sin;

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = INADDR_ANY;
	return (sin);
}

static int				bind_socket(int sock, t_sockaddr_in *sin)
{
	int		res;

	res = bind(sock, (t_sockaddr *)sin, sizeof(t_sockaddr_in));
	if (res == -1)
		ft_printf(2, "[!] Can't bind socket: (%d)\n", res);
	return (res);
}

static int				listen_socket(int sock)
{
	int		res;

	if ((res = listen(sock, MAX_USER)) == -1)
		ft_printf(2, "[!] Can't create socket stream\n");
	if (1 == 2)
		ft_printf(1, "%s[!] listen(sock, %d)%s\n", RED, MAX_USER, RESET);
	return (sock);
}

int						init_stream_server(t_env *e)
{
	if ((e->srv_sock = get_socket_stream()) == -1)
		return (-1);
	e->sin = get_sockaddr(e->srv_port);
	if (bind_socket(e->srv_sock, &e->sin) == -1)
		return (-1);
	if (listen_socket(e->srv_sock) == -1)
		return (-1);
	ft_printf(1, "[*] Server launched on Port %d\n", e->srv_port);
	return (0);
}
