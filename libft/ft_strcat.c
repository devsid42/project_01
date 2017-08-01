/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 21:10:00 by avasseur          #+#    #+#             */
/*   Updated: 2015/01/22 17:23:48 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int		i;
	int		len;

	if (s1 != NULL && s2 != NULL)
	{
		i = 0;
		len = ft_strlen(s1);
		while (s2[i] != '\0')
		{
			s1[i + len] = s2[i];
			i++;
		}
		s1[i + len] = '\0';
		return (s1);
	}
	return (NULL);
}