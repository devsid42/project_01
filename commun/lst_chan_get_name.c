/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_chan_get_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:23:48 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/29 20:20:07 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

char	*lst_chan_get_name(t_chan *chans, char *name)
{
	t_chan	*l;

	if (!chans)
		return (NULL);
	l = chans;
	while (l)
	{
		if (ft_sec_strnccmp(l->name, name, NICK_SIZE - 1) == SAME)
		{
			return (l->name);
		}
		l = l->next;
	}
	return (NULL);
}
