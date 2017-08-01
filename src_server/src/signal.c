/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:00:59 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/29 15:34:11 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static void		signal_action(int sig)
{
	int		i;

	ft_printf(1, "\n[*] Closing properly server (%d)\n", sig);
	i = 4;
	while (i < MAX_USER)
	{
		ft_printf(1, "\rClosing sockets: %d", i);
		usleep(300);
		close(i);
		i += 1;
	}
	close(3);
	ft_printf(1, "\rClosing sockets: DONE\n");
	exit(0);
}

void			handle_signal(void)
{
	signal(SIGINT, &signal_action);
	signal(SIGQUIT, &signal_action);
	signal(SIGTERM, &signal_action);
	signal(SIGSTOP, &signal_action);
}
