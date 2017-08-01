/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_channel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 23:44:45 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/24 19:45:58 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static size_t	get_channel_len(char *buf)
{
	size_t	len;

	len = 0;
	if (!buf)
		return (0);
	buf += 1;
	while (*buf)
	{
		if (!ft_isalnum(*buf))
			break ;
		buf += 1;
		len += 1;
	}
	return (len);
}

char			*get_channel(char *buf)
{
	size_t	len;
	char	*channel;

	if (!buf)
		return (NULL);
	if (!(buf = ft_strchr(buf, '#')))
		return (NULL);
	if ((len = get_channel_len(buf)) == 0)
		return (NULL);
	len += 1;
	if (!(channel = ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strncpy(channel, buf, len);
	return (channel);
}
