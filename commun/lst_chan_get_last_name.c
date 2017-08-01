/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_chan_get_last_name.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 21:50:57 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/24 19:46:59 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

char	*lst_chan_get_last_name(t_chan *chans)
{
	t_chan	*l;

	if (!chans)
		return (NULL);
	l = chans;
	while (l->next)
		l = l->next;
	return (l->name);
}
