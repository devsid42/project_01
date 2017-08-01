/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freearray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/30 17:23:41 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/27 18:45:14 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freearray(char **a)
{
	int		i;

	if (!a)
		return ;
	i = 0;
	while (a[i])
	{
		ft_strdel(&a[i]);
		i++;
	}
	free(a);
	a = NULL;
}
