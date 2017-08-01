/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_chan_is.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 19:41:39 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/24 19:47:20 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

int		lst_chan_is(t_chan *chans, char *name)
{
	t_chan	*l;

	if (!chans || !name)
		return (0);
	l = chans;
	while (l)
	{
		if (ft_strncmp(name, l->name, MSG_SIZE) == 0)
			return (1);
		l = l->next;
	}
	return (0);
}
