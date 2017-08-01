/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stream_client.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 20:35:21 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 19:21:12 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

static int				get_socket_stream(void)
{
	int		sock;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ft_printf(2, "[!] Can't create socket stream\n");
	return (sock);
}

static t_sockaddr_in	get_sock_addr(int port, t_in_addr *addr)
{
	t_sockaddr_in	sin;

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr = *addr;
	return (sin);
}

static int				set_getaddrinfo(const char *ip, t_in_addr *addr)
{
	t_addrinfo		*res;

	if (getaddrinfo(ip, 0, 0, &res) != GETADDRINFO_OK)
	{
		ft_printf(2, "[!] getaddrinfo error\n");
		return (-1);
	}
	*addr = ((t_sockaddr_in *)res->ai_addr)->sin_addr;
	ip = ft_strdup(inet_ntoa(*addr));
	ft_printf(1, "Ip: %s\n", ip);
	freeaddrinfo(res);
	return (0);
}

static int				connect_socket(int sock, t_sockaddr *sin)
{
	if (connect(sock, sin, sizeof(t_sockaddr_in)) == -1)
	{
		ft_printf(1, "[!] Can't create socket stream\n");
		return (-1);
	}
	return (sock);
}

int						init_stream_client(t_env *e)
{
	if ((e->sock = get_socket_stream()) == -1)
		return (-1);
	if (set_getaddrinfo(e->ip, &e->addr) == -1)
		return (-1);
	e->sin = get_sock_addr(e->port, &e->addr);
	if (connect_socket(e->sock, (t_sockaddr *)&e->sin) == -1)
		return (-1);
	ft_printf(1, "[*] Connexion to Server %s, Port: %d\n",\
		e->ip, e->port);
	return (0);
}
