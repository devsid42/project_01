/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_credential.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 22:52:49 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:19:24 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

void	send_credential(int sock, char *nick, char *user)
{
	ft_bprintf(sock, MSG_SIZE, "NICK %s\n", nick);
	ft_bprintf(sock, MSG_SIZE, "USER %s %s_ %s %s\n", user, user, user, user);
}
