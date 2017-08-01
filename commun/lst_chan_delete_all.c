/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_chan_delete_all.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 19:34:18 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/24 19:44:33 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

int		lst_chan_delete_all(t_chan **chans)
{
	t_chan	*l;

	if (!chans || !(*chans))
		return (0);
	l = *chans;
	while (l->next)
	{
		l = l->next;
		free(l->prev);
	}
	free(l);
	*chans = NULL;
	return (1);
}
