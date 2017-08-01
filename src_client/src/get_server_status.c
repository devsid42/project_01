/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_server_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 18:50:10 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/24 22:43:42 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

void	get_server_status(char *buf)
{
	if (!buf || *buf == 0)
		ft_printf(1, "\n[*] Server closed\n");
	else
		return ;
	exit(0);
}
