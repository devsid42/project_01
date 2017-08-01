/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_client_is_reg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 18:11:05 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/29 20:47:17 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

int			lst_client_is_reg(t_client *cnt, int sock)
{
	t_client	*l;
	int			is_reg;

	if (!cnt)
		return (-1);
	is_reg = 0;
	l = cnt;
	while (l)
	{
		if (l->sock == sock)
		{
			if (*(l->user))
				is_reg = 1;
			if (*(l->nick))
				is_reg += 1;
			return (is_reg);
		}
		l = l->next;
	}
	return (0);
}
